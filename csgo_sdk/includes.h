#pragma once

// fuck c++.
#pragma disable(warning : 4996)

// some defines.
#define DECL_ALIGN(x)			__declspec(align(x))

#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)

#define NUM_ENT_ENTRY_BITS (11 + 2)
#define NUM_ENT_ENTRIES	(1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS	16
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK ((1 << NUM_SERIAL_NUM_BITS) - 1)

#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1
#define MAX_FLOWS 2		

#include <Windows.h>
#include <stdint.h>
#include <fstream>
#include <chrono>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <thread>
#include <memory>
#include <cstdint>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <TlHelp32.h>
#include <cmath>
#include <algorithm>
#include <array>
#include <windowsx.h>
#include <intrin.h>
#include <ShlObj.h>
#include <any>
#include <filesystem>
#include <winternl.h>