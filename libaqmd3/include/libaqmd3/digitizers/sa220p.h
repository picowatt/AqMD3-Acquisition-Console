#ifndef SA220P_H
#define SA220P_H

#include "../digitizer.h"
#include "../devicevalues/deviceconstants.h"


class SA220P : public Digitizer {
public:
	 typedef struct Info{
		std::string instrument_model;
		std::string firmware_revision;
		std::string serial_number;
	} Info;

	inline static const std::string channel_1 = "Channel1";
	inline static const std::string channel_2 = "Channel2";

	inline static const  std::string samples_channel_1 = "StreamCh1";
	inline static const std::string samples_channel_2 = "StreamCh2";
	inline static const  std::string markers_channel_1 = "MarkersCh1";
	inline static const  std::string markers_channel_2 = "MarkersCh2";

	inline static const std::string trigger_internal_1 = "Internal1";
	inline static const std::string trigger_internal_2 = "Internal2";
	inline static const  std::string trigger_external = "External1";
	inline static const  std::string trigger_software = "Software";
	inline static const  std::string trigger_self = "SelfTrigger";

	inline static const  std::string control_io_1 = "ControlIO1";
	inline static const std::string control_io_2 = "ControlIO2";
	inline static const  std::string control_io_3 = "ControlIO3";

	static std::string visa_device_id;
	static std::string options;

	inline static const double full_scale_range_0_5v = 0.5;
	inline static const double full_scale_range_2_5v = 2.5;

	inline static const  double sample_rate_1GS = 1000000000.0;
	inline static const  double sample_rate_2GS = 2000000000.0;

private:
	Info digitizer_info;
	
	Info get_digitizer_info()
	{
		std::string firmware_rev(256, (char)0);
		Digitizer::get_instrument_firmware_revision(firmware_rev);
		firmware_rev.resize(strlen(firmware_rev.c_str()));

		std::string serial_num(256, (char)0);
		Digitizer::get_instrument_serial_number(serial_num);
		serial_num.resize(strlen(serial_num.c_str()));

		std::string model(256, (char)0);
		Digitizer::get_instrument_model(model);
		serial_num.resize(strlen(model.c_str()));

		return Info{ model, firmware_rev, serial_num };
	}

public:
	SA220P(std::string device_handle, bool simulate_device) : Digitizer(device_handle, simulate_device, "SA220P")
	{
		digitizer_info = get_digitizer_info();
	}

	void set_sampling_rate(double rate) const;
	void set_record_size(uint64_t elements) const;
	void set_trigger_parameters(std::string trigger, double level, bool isRisingEdgeTriggered, double trigger_delay_ms) const;
	void set_channel_parameters(std::string channel, double range, double offset) const;
	void set_channel_data_inversion(std::string channel, bool enable) const;

	Info get_info() const { return digitizer_info; };

	void enable_io_port(const std::string& io_port) const;
	void disable_io_port(const std::string& io_port) const;

	bool get_is_idle() const;

	std::shared_ptr<StreamingContext> configure_cst(std::string channel, std::shared_ptr<AcquisitionBufferPool> buffer_pool) const override;
	std::shared_ptr<StreamingContext> configure_cst(std::string channel, std::shared_ptr<AcquisitionBufferPool>, ZeroSuppressParameters parameters) const override;
};

template <>
struct DeviceConstants<SA220>
{
	static DeviceConstantsMap get_device_constants_map()
	{
		auto device_constants = DeviceConstantsMap {
			{DigitizerConfigurableType::ChannelValues, std::vector<std::string>{SA220::channel_1, SA220::channel_2}},
			{DigitizerConfigurableType::SampleChannelValues, std::vector<std::string>{SA220::samples_channel_1, SA220::samples_channel_2}},
			{DigitizerConfigurableType::MarkersChannelValues, std::vector<std::string>{SA220::markers_channel_1, SA220::markers_channel_2}},
			{DigitizerConfigurableType::TriggerValues, std::vector<std::string>{SA220::trigger_internal_1, SA220::trigger_internal_2, SA220::trigger_external, SA220::trigger_software, SA220::trigger_self}},
			{DigitizerConfigurableType::ControlIOValues, std::vector<std::string>{SA220::control_io_1, SA220::control_io_2, SA220::control_io_3}},
			{DigitizerConfigurableType::FullScaleRangeValues, std::vector<double>{SA220::full_scale_range_0_5v, SA220::full_scale_range_2_5v}},
			{DigitizerConfigurableType::SampleRateValues, std::vector<double>{SA220::sample_rate_1GS, SA220::sample_rate_2GS}}
		};

		return device_constants;
	}
};

#endif // !SA220P_H
