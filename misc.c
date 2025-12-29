/*
 * SPDX-License-Identifier: 0BSD AND BSD-3-Clause
 *
 * This file contains code derived from the tcsh project.
 *
 * Copyright (C) 2025 Matheus Garcia
 * 
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <AL/alut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "main.h"

static char strnull[] = "";

void entrytok(char *entry, struct configfn *cfgfnp)
{
  entry += strlen(cfgfnp->name);
  cfgfnp->val = quotetok(entry);
  if(cfgfnp->val == strnull) {
    fprintf(stderr, "%s is missing a value", cfgfnp->name);
    exit(1);
  }
}

char *quotetok(char *buf)
{
  struct strbuf ret = strbuf_init;

  while(*buf != '\0')
    if(*buf++ == '"') {
      while(*buf != '\0') {
        if(buf[0] == '"') {
          if(buf[1] == '"') {
            strbuf_appendn(&ret, buf, (size_t) 2);
	    buf += 2;
	    continue;
	  }
	  break;
	}
	strbuf_append1(&ret, *buf++);
      }
      break;
    }
  if(ret.len == 0)
    return strnull;
  return strbuf_finish(&ret);
}

#define DO_STRBUF(STRBUF, CHAR, STRLEN)				\
								\
struct STRBUF *							\
STRBUF##_alloc(void)						\
{								\
    return calloc(1, sizeof(struct STRBUF));			\
}								\
								\
static void							\
STRBUF##_store1(struct STRBUF *buf, CHAR c)			\
{								\
    if (buf->size == buf->len) {				\
	if (buf->size == 0)					\
	    buf->size = 64; /* Arbitrary */			\
	else							\
	    buf->size *= 2;					\
	buf->s = realloc(buf->s, buf->size * sizeof(*buf->s));	\
    }								\
    assert(buf->s);						\
    buf->s[buf->len] = c;					\
}								\
								\
/* Like strbuf_append1(buf, '\0'), but don't advance len */	\
void								\
STRBUF##_terminate(struct STRBUF *buf)				\
{								\
    STRBUF##_store1(buf, '\0');					\
}								\
								\
void								\
STRBUF##_append1(struct STRBUF *buf, CHAR c)			\
{								\
    STRBUF##_store1(buf, c);					\
    buf->len++;							\
}								\
								\
void								\
STRBUF##_appendn(struct STRBUF *buf, const CHAR *s, size_t len)	\
{								\
    if (buf->size < buf->len + len) {				\
	if (buf->size == 0)					\
	    buf->size = 64; /* Arbitrary */			\
	while (buf->size < buf->len + len)			\
	    buf->size *= 2;					\
	buf->s = realloc(buf->s, buf->size * sizeof(*buf->s));	\
    }								\
    memcpy(buf->s + buf->len, s, len * sizeof(*buf->s));	\
    buf->len += len;						\
}								\
								\
void								\
STRBUF##_append(struct STRBUF *buf, const CHAR *s)		\
{								\
    STRBUF##_appendn(buf, s, STRLEN(s));			\
}								\
								\
CHAR *								\
STRBUF##_finish(struct STRBUF *buf)				\
{								\
    STRBUF##_append1(buf, 0);					\
    return realloc(buf->s, buf->len * sizeof(*buf->s));		\
}								\
								\
void								\
STRBUF##_cleanup(void *xbuf)					\
{								\
    struct STRBUF *buf;						\
								\
    buf = xbuf;							\
    free(buf->s);						\
}								\
								\
void								\
STRBUF##_free(void *xbuf)					\
{								\
    STRBUF##_cleanup(xbuf);					\
    free(xbuf);							\
}

DO_STRBUF(strbuf, char, strlen);
