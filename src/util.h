#ifndef fooutilhfoo
#define fooutilhfoo

/* $Id$ */

/***
  This file is part of nss-mdns.
 
  nss-mdns is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.
 
  nss-mdns is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with nss-mdns; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include <stdio.h>
#include <resolv.h>

int set_cloexec(int fd);
int ends_with(const char *name, const char *suffix);

// Returns true if we should try to resolve the name with mDNS.
//
// If mdns_allow_file is NULL, then this implements the "local" SOA
// check and two-label name checks similarly to the algorithm
// described at https://support.apple.com/en-us/HT201275. This means
// that if a unicast DNS server claims authority on "local", or if the
// user tries to resolve a >2-label name, we will not do mDNS resolution.
//
// The two heuristics described above are disabled if mdns_allow_file
// is not NULL.
int verify_name_allowed_with_soa(const char *name, FILE *mdns_allow_file);

enum verify_name_result {
    VERIFY_NAME_RESULT_NOT_ALLOWED,
    VERIFY_NAME_RESULT_ALLOWED_IF_NO_LOCAL_SOA,
    VERIFY_NAME_RESULT_ALLOWED
};

// Tells us if the name is not allowed unconditionally, allowed only
// if local_soa() returns false, or unconditionally allowed.
enum verify_name_result verify_name_allowed(const char *name,
                                            FILE *mdns_allow_file);

// Returns true if a DNS server claims authority over "local".
int local_soa(void);

// Returns the number of labels in a name.
int label_count(const char *name);

#endif
