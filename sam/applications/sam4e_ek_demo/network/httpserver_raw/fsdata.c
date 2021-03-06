/**
 * \file
 *
 * \brief Virtual file system management.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "lwipopts.h"
#if defined(HTTP_RAW_USED)

#include <string.h>
#include "fsdata.h"

#include "compiler.h"
#include "excan.h"
#include "jqflot.h"
#include "jquery.h"
#include "style.h"
#include "index.h"
#include "favicon.h"
#include "atmel.h"

static const unsigned char data_404_html[] = {
  0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x30, 0x20, 0x34,
  0x30, 0x34, 0x20, 0x46, 0x69, 0x6c, 0x65, 0x20, 0x6e, 0x6f,
  0x74, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0xd, 0xa, 0x53,
  0x65, 0x72, 0x76, 0x65, 0x72, 0x3a, 0x20, 0x6c, 0x77, 0x49,
  0x50, 0x2f, 0x70, 0x72, 0x65, 0x2d, 0x30, 0x2e, 0x36, 0x20,
  0x28, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77,
  0x77, 0x2e, 0x73, 0x69, 0x63, 0x73, 0x2e, 0x73, 0x65, 0x2f,
  0x7e, 0x61, 0x64, 0x61, 0x6d, 0x2f, 0x6c, 0x77, 0x69, 0x70,
  0x2f, 0x29, 0xd, 0xa, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e,
  0x74, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x3a, 0x20, 0x74, 0x65,
  0x78, 0x74, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0xd, 0xa, 0xd,
  0xa, 0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0xa, 0x3c, 0x68,
  0x65, 0x61, 0x64, 0x3e, 0x3c, 0x74, 0x69, 0x74, 0x6c, 0x65,
  0x3e, 0x6c, 0x77, 0x49, 0x50, 0x20, 0x2d, 0x20, 0x41, 0x20,
  0x4c, 0x69, 0x67, 0x68, 0x74, 0x77, 0x65, 0x69, 0x67, 0x68,
  0x74, 0x20, 0x54, 0x43, 0x50, 0x2f, 0x49, 0x50, 0x20, 0x53,
  0x74, 0x61, 0x63, 0x6b, 0x3c, 0x2f, 0x74, 0x69, 0x74, 0x6c,
  0x65, 0x3e, 0x3c, 0x2f, 0x68, 0x65, 0x61, 0x64, 0x3e, 0xa,
  0x3c, 0x62, 0x6f, 0x64, 0x79, 0x20, 0x62, 0x67, 0x63, 0x6f,
  0x6c, 0x6f, 0x72, 0x3d, 0x22, 0x77, 0x68, 0x69, 0x74, 0x65,
  0x22, 0x20, 0x74, 0x65, 0x78, 0x74, 0x3d, 0x22, 0x62, 0x6c,
  0x61, 0x63, 0x6b, 0x22, 0x3e, 0xa, 0xa, 0x20, 0x20, 0x20,
  0x20, 0x3c, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x77, 0x69,
  0x64, 0x74, 0x68, 0x3d, 0x22, 0x31, 0x30, 0x30, 0x25, 0x22,
  0x3e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x74,
  0x72, 0x20, 0x76, 0x61, 0x6c, 0x69, 0x67, 0x6e, 0x3d, 0x22,
  0x74, 0x6f, 0x70, 0x22, 0x3e, 0x3c, 0x74, 0x64, 0x20, 0x77,
  0x69, 0x64, 0x74, 0x68, 0x3d, 0x22, 0x38, 0x30, 0x22, 0x3e,
  0x9, 0x20, 0x20, 0xa, 0x9, 0x20, 0x20, 0x3c, 0x61, 0x20,
  0x68, 0x72, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70,
  0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x73, 0x69, 0x63,
  0x73, 0x2e, 0x73, 0x65, 0x2f, 0x22, 0x3e, 0x3c, 0x69, 0x6d,
  0x67, 0x20, 0x73, 0x72, 0x63, 0x3d, 0x22, 0x69, 0x6d, 0x67,
  0x2f, 0x73, 0x69, 0x63, 0x73, 0x2e, 0x67, 0x69, 0x66, 0x22,
  0xa, 0x9, 0x20, 0x20, 0x62, 0x6f, 0x72, 0x64, 0x65, 0x72,
  0x3d, 0x22, 0x30, 0x22, 0x20, 0x61, 0x6c, 0x74, 0x3d, 0x22,
  0x53, 0x49, 0x43, 0x53, 0x20, 0x6c, 0x6f, 0x67, 0x6f, 0x22,
  0x20, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x3d, 0x22, 0x53, 0x49,
  0x43, 0x53, 0x20, 0x6c, 0x6f, 0x67, 0x6f, 0x22, 0x3e, 0x3c,
  0x2f, 0x61, 0x3e, 0xa, 0x9, 0x3c, 0x2f, 0x74, 0x64, 0x3e,
  0x3c, 0x74, 0x64, 0x20, 0x77, 0x69, 0x64, 0x74, 0x68, 0x3d,
  0x22, 0x35, 0x30, 0x30, 0x22, 0x3e, 0x9, 0x20, 0x20, 0xa,
  0x9, 0x20, 0x20, 0x3c, 0x68, 0x31, 0x3e, 0x6c, 0x77, 0x49,
  0x50, 0x20, 0x2d, 0x20, 0x41, 0x20, 0x4c, 0x69, 0x67, 0x68,
  0x74, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x20, 0x54, 0x43,
  0x50, 0x2f, 0x49, 0x50, 0x20, 0x53, 0x74, 0x61, 0x63, 0x6b,
  0x3c, 0x2f, 0x68, 0x31, 0x3e, 0xa, 0x9, 0x20, 0x20, 0x3c,
  0x68, 0x32, 0x3e, 0x34, 0x30, 0x34, 0x20, 0x2d, 0x20, 0x50,
  0x61, 0x67, 0x65, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f,
  0x75, 0x6e, 0x64, 0x3c, 0x2f, 0x68, 0x32, 0x3e, 0xa, 0x9,
  0x20, 0x20, 0x3c, 0x70, 0x3e, 0xa, 0x9, 0x20, 0x20, 0x20,
  0x20, 0x53, 0x6f, 0x72, 0x72, 0x79, 0x2c, 0x20, 0x74, 0x68,
  0x65, 0x20, 0x70, 0x61, 0x67, 0x65, 0x20, 0x79, 0x6f, 0x75,
  0x20, 0x61, 0x72, 0x65, 0x20, 0x72, 0x65, 0x71, 0x75, 0x65,
  0x73, 0x74, 0x69, 0x6e, 0x67, 0x20, 0x77, 0x61, 0x73, 0x20,
  0x6e, 0x6f, 0x74, 0x20, 0x66, 0x6f, 0x75, 0x6e, 0x64, 0x20,
  0x6f, 0x6e, 0x20, 0x74, 0x68, 0x69, 0x73, 0xa, 0x9, 0x20,
  0x20, 0x20, 0x20, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2e,
  0x20, 0xa, 0x9, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x3e, 0xa,
  0x9, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x74, 0x64, 0x3e,
  0xa, 0x9, 0x20, 0x20, 0x26, 0x6e, 0x62, 0x73, 0x70, 0x3b,
  0xa, 0x9, 0x3c, 0x2f, 0x74, 0x64, 0x3e, 0x3c, 0x2f, 0x74,
  0x72, 0x3e, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
  0x2f, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0xa, 0x3c, 0x2f,
  0x62, 0x6f, 0x64, 0x79, 0x3e, 0xa, 0x3c, 0x2f, 0x68, 0x74,
  0x6d, 0x6c, 0x3e, 0xa, };

/** Linked list of the virtual file system content. */
const struct fsdata_file file_atmel_png[] = {{NULL, "etc/img/atmel.png", atmel, sizeof(atmel)}};
const struct fsdata_file file_favicon_ico[] = {{file_atmel_png, "favicon.ico", favicon, sizeof(favicon)}};
const struct fsdata_file file_style_css[] = {{file_favicon_ico, "etc/style.css", style, sizeof(style)}};
const struct fsdata_file file_jquery_js[] = {{file_style_css, "etc/js/jquery.js", jquery, sizeof(jquery)}};
const struct fsdata_file file_jqflot_js[] = {{file_jquery_js, "etc/js/jqflot.js", jqflot, sizeof(jqflot)}};
const struct fsdata_file file_excan_js[] = {{file_jqflot_js, "etc/js/excan.js", excan, sizeof(excan)}};
const struct fsdata_file file_404_html[] = {{file_excan_js, "404.html", data_404_html, sizeof(data_404_html)}};
const struct fsdata_file file_index_html[] = {{file_404_html, "index.html", index_html, sizeof(index_html)}};

#endif
