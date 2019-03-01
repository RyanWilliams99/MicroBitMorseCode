#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2019 // UTC year
#define YOTTA_BUILD_MONTH 3 // UTC month 1-12
#define YOTTA_BUILD_DAY 1 // UTC day 1-31
#define YOTTA_BUILD_HOUR 10 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 44 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 41 // UTC second 0-61
#define YOTTA_BUILD_UUID 060bc5f2-0fd9-432f-9805-5f003b301fdd // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 5073337552e7d6dc938ac5c890ee0287357f454a // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 5073337 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
