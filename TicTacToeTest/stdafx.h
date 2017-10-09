// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// google test and mock
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define NEVER_TRANSLATE(x) _T(x)
#define NEVER_TRANSLATEA(x)   x
#define NEVER_TRANSLATEL(x) L ## x
#define NEVER_TRANSLATEQ(x)   x
