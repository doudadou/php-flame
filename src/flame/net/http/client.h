#pragma once

// 所有导出到 PHP 的函数必须符合下面形式：
// php::value fn(php::parameters& params);
namespace flame {
namespace net {
namespace http {

	class client: public php::class_base {
	public:
		client();
		~client() {
			release();
		}
		php::value __construct(php::parameters& params);
		void release();
		// 执行
		php::value exec(php::parameters& params);
		php::value exec(php::object& request);
		php::value debug(php::parameters& params);


	private:
		// curl要用的回调
		static void curl_check_multi_info(client* cli);
		static int  curl_handle_socket(CURL* easy, curl_socket_t s, int action, void *userp, void *socketp);
		static int  curl_start_timeout(CURLM* multi, long timeout_ms, void* userp);
		static void curl_timeout_cb(uv_timer_t *req);
		static void curl_perform(uv_poll_t *req, int status, int events);

		CURLM*     curlm_;
		int        debug_;
		uv_timer_t timer_;
	};
	extern client* default_client;
	php::value get(php::parameters& params);
	php::value post(php::parameters& params);
	php::value put(php::parameters& params);

}
}
}
