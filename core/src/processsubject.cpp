#include "../include/processsubject.h"
#include "../include/util//timehelpers.h"
#include "../include/uimf/uimfacquisitionrecord.h"
#include <numeric>
#include <format>
#include <spdlog/spdlog.h>

// static int delta = 100; // TODO: move to config

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void ProcessSubject::on_notify(UimfAcquisitionRecord& item)
{
	try
	{
		//uint64_t avg_ts = 0;
		//for (int i = 1; i < ad.stamps.size(); i++)
		//{
		//	avg_ts += (ad.stamps[i].timestamp - ad.stamps[i - 1].timestamp);
		//	if ((ad.stamps[i].index - ad.stamps[i - 1].index) > 1)
		//	{
		//		spdlog::debug(std::format("ad.stamps[i].index: {} --  ad.stamps[i - 1].index: {}", ad.stamps[i].index, ad.stamps[i - 1].index));
		//		spdlog::debug(std::format("i: {} --  ad.stamps().size(): {}", i, ad.stamps.size()));
		//		spdlog::debug(std::format("total_triggers_processed: {}", total_triggers_processed));
		//	}
		//}
		//avg_ts /= ad.stamps.size() - 1;

		//// Determine if the initially measured period (in samples) of the clock pulse, tof_avg_samples, differs by more than delta
		//// from the last group of measured scan data's averaged timestamps. Warn if it's the case since the record size was determined using the 
		//// initial value.
		//if (avg_ts > (tof_avg_samples + delta) || avg_ts < (tof_avg_samples - delta))
		//{
		//	spdlog::warn(std::format("Successive recorded trigger event timestamps differ by more than {} samples", delta));
		//	spdlog::warn(std::format("Last {} recorded timestamps avg (in samples):\t {}", ad.stamps.size(), avg_ts));
		//	spdlog::warn(std::format("Expected avg (in samples):\t {} +/- {}", tof_avg_samples, delta));
		//}

		auto result = item.to_frame();
		auto notify_type = result->parameters().file_name.empty() ? SubscriberType::ACQUIRE : SubscriberType::BOTH;
		Publisher<frame_ptr>::notify(result, notify_type);
	}
	catch (const std::exception& ex)
	{
		spdlog::error(std::format("Processing error: {}", ex.what()));
		spdlog::error(std::format("Processing subject unprocessed elements: ", items.size()));
	}
	catch (...)
	{
		spdlog::error("Unknown processing error");
		spdlog::error(std::format("Processing subject unprocessed elements: ", items.size()));
	}
}