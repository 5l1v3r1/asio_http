/**
    asio_http: http client library for boost asio
    Copyright (c) 2017-2019 Julio Becerra Gomez
    See COPYING for license information.
*/

#ifndef ASIO_HTTP_HTTP_REQUEST_RESULT_H
#define ASIO_HTTP_HTTP_REQUEST_RESULT_H

#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <system_error>
#include <vector>

namespace asio_http
{
class http_request_interface;

struct http_request_stats
{
  std::chrono::duration<double> name_lookup_time_s;
  std::chrono::duration<double> total_time_s;
  std::int64_t                  avg_download_speed_bps;
  std::int64_t                  avg_upload_speed_bps;
  std::int64_t                  downloaded_bytes;
  std::int64_t                  uploaded_bytes;
};

class http_request_result
{
public:
  http_request_result(std::uint32_t             http_response_code_,
                      std::vector<std::string>  headers_,
                      std::vector<std::uint8_t> content_,
                      std::error_code           error_,
                      http_request_stats        request_stats_)
      : http_response_code(http_response_code_)
      , headers(std::move(headers_))
      , content_body(std::move(content_))
      , error(error_)
      , stats(std::move(request_stats_))
  {
  }
  http_request_result() {}

  // Non const to allow move semantics
  std::uint32_t             http_response_code;
  std::vector<std::string>  headers;
  std::vector<std::uint8_t> content_body;
  std::error_code           error;
  http_request_stats        stats;

  std::string get_body_as_string() const { return { content_body.begin(), content_body.end() }; }
};
}  // namespace asio_http

#endif
