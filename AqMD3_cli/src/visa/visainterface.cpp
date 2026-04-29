#include "../../include/visa/visainterface.h"

namespace 
{
    template <typename FirstClosable, typename... RestClosable>
    std::unexpected<std::string> get_visa_status_and_return_unexpected(ViSession session, ViStatus status, FirstClosable first, RestClosable... rest)
    {
        char status_description[1024] = { 0 };

        viStatusDesc(session, status, status_description);

        viClose(first);
        (viClose(rest), ...);

        return std::unexpected(std::string(status_description));
    }
}

namespace visa_interface
{
    std::expected<std::vector<std::string>, std::string> get_device_list()
    {
        std::vector<std::string> device_list;

        ViStatus rc;
        ViChar search[] = "PXI?*::INSTR";
        ViFindList viList;
        ViUInt32 count = 0;
        ViChar rsrc[256];
        ViSession rm;
        rc = viOpenDefaultRM(&rm);

        if (rc < VI_SUCCESS)
        {
            return get_visa_status_and_return_unexpected(rm, rc, rm);
        }

        rc = viFindRsrc(rm, search, &viList, &count, rsrc);
        if (rc < VI_SUCCESS)
        {
            return get_visa_status_and_return_unexpected(rm, rc, rm);
        }
        device_list.emplace_back(rsrc);
        count--;

        while (count > 0)
        {
            rc = viFindNext(viList, rsrc);
            if (rc < VI_SUCCESS)
            {
                return get_visa_status_and_return_unexpected(rm, rc, rm, viList);
            }
            device_list.emplace_back(rsrc);
            count--;
        }

        viClose(viList);
        viClose(rm);

        return device_list;
    }
}