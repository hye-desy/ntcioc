#pragma once

#include <map>
#include <mutex>

/** Measurements available for one channel. */
struct result {
    float ch0;
    float ch1;
    float ch2;
    float ch3;
    float ch4;
    float ch5;
    float ch6;
    float ch7;
    bool ok = false;
};


class result_list {
    public:
	static result_list* instance();
	result get_result(uint8_t _device);
	void update_result(uint8_t _device, result&& _result);

    protected:
	std::map<uint8_t, result> m_results;
	std::mutex m_result_mutex;
};
