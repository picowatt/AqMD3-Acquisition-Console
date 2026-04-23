#ifndef DIGITIZER_CONFIGURABLE_TYPE_H
#define DIGITIZER_CONFIGURABLE_TYPE_H


namespace aqmd3
{
        enum class DigitizerConfigurableType
        {
            ChannelValues,
            SampleChannelValues,
            MarkersChannelValues,
            TriggerValues,
            ControlIOValues,
            FullScaleRangeValues,
            SampleRateValues
        };
}

#endif