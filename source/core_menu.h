#pragma once

#include <stdint.h>

namespace core
{
#ifdef ANDROID

	static uint8_t gta3_menu_script[] = {
		0xA4, 0x03, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x00, 0x78, 0x06, 0xE5, 0x03, 0x43, 0x4C, 0x44, 0x53,
		0x43, 0x4C, 0x00, 0x00, 0x01, 0x00, 0x05, 0xD0, 0x07, 0xF0, 0x0D, 0xEE, 0x0D, 0x03, 0x0C, 0x00,
		0x03, 0x0D, 0x00, 0xD0, 0x0D, 0x03, 0x00, 0x00, 0x01, 0x5A, 0xFE, 0xFF, 0xFF, 0xD1, 0x0D, 0x03,
		0x0E, 0x00, 0x03, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0xDD, 0x0D, 0x03, 0x00, 0x00, 0x04, 0x00,
		0xD6, 0x00, 0x04, 0x15, 0x39, 0x00, 0x03, 0x00, 0x00, 0x04, 0x01, 0x56, 0x82, 0x02, 0x10, 0x02,
		0x4D, 0x00, 0x01, 0xA2, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x61, 0xFE, 0xFF, 0xFF, 0xD6, 0x00,
		0x04, 0x00, 0xEE, 0x83, 0x02, 0x10, 0x02, 0x4D, 0x00, 0x01, 0x8B, 0xFF, 0xFF, 0xFF, 0x02, 0x00,
		0x01, 0x61, 0xFE, 0xFF, 0xFF, 0xE1, 0x0D, 0x03, 0x02, 0x00, 0x04, 0x04, 0x04, 0x06, 0x04, 0x00,
		0x05, 0xDC, 0x05, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x02, 0x00, 0x04, 0x00, 0x4D, 0x00,
		0x01, 0x64, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x61, 0xFE, 0xFF, 0xFF, 0xDC, 0x0D, 0x04, 0x00,
		0x04, 0x01, 0xF1, 0x0D, 0xD0, 0x0D, 0x03, 0x00, 0x00, 0x01, 0x44, 0xFE, 0xFF, 0xFF, 0xF2, 0x0D,
		0x03, 0x00, 0x00, 0x03, 0x0C, 0x00, 0xF5, 0x0D, 0x03, 0x0B, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39,
		0x00, 0x03, 0x0C, 0x00, 0x04, 0x00, 0x4D, 0x00, 0x01, 0x23, 0xFF, 0xFF, 0xFF, 0xE6, 0x03, 0x01,
		0x00, 0x04, 0x64, 0xE5, 0x03, 0x43, 0x4C, 0x4D, 0x4E, 0x55, 0x4E, 0x00, 0x00, 0xD8, 0x0D, 0x03,
		0x0F, 0x00, 0x03, 0x0E, 0x00, 0x04, 0x04, 0x04, 0x00, 0xD9, 0x0D, 0x03, 0x0E, 0x00, 0x04, 0x02,
		0x04, 0x04, 0x04, 0x00, 0x04, 0x00, 0xB4, 0x01, 0x02, 0x10, 0x02, 0x04, 0x00, 0x01, 0x00, 0x04,
		0x32, 0x73, 0x03, 0x01, 0x00, 0x04, 0x00, 0xF4, 0x0D, 0x03, 0x0A, 0x00, 0x04, 0x64, 0xD6, 0x00,
		0x04, 0x01, 0x29, 0x00, 0x03, 0x0A, 0x00, 0x04, 0x00, 0x2D, 0x80, 0x03, 0x0A, 0x00, 0x03, 0x0C,
		0x00, 0x4D, 0x00, 0x01, 0xA7, 0xFE, 0xFF, 0xFF, 0xE6, 0x03, 0x01, 0x00, 0x04, 0x64, 0xEF, 0x0D,
		0x03, 0x00, 0x00, 0x03, 0x0A, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x00, 0x00, 0x04,
		0x02, 0x4D, 0x00, 0x01, 0xAE, 0xFE, 0xFF, 0xFF, 0xE5, 0x03, 0x43, 0x4C, 0x4D, 0x4E, 0x55, 0x31,
		0x00, 0x00, 0x02, 0x00, 0x01, 0x83, 0xFE, 0xFF, 0xFF, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03,
		0x0A, 0x00, 0x04, 0xFE, 0x4D, 0x00, 0x01, 0x8A, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x64, 0x02,
		0x00, 0x01, 0x83, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xFD, 0xFE, 0xFF, 0xFF, 0xF6, 0x0D, 0x03,
		0x0B, 0x00, 0xD9, 0x0D, 0x03, 0x0E, 0x00, 0x03, 0x0F, 0x00, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00,
		0xF3, 0x0D, 0xB4, 0x01, 0x02, 0x10, 0x02, 0x04, 0x01, 0xDC, 0x0D, 0x04, 0x00, 0x04, 0x00, 0x02,
		0x00, 0x01, 0xCB, 0xFF, 0xFF, 0xFF, 0x4D, 0x61, 0x72, 0x6B, 0x65, 0x74, 0x69, 0x6E, 0x67, 0x5F,
		0x48, 0x75, 0x64, 0x44, 0x69, 0x73, 0x61, 0x62, 0x6C, 0x65, 0x64, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x43, 0x4C, 0x45, 0x4F, 0x20, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x43, 0x4C, 0x4F, 0x53, 0x45, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x31, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x31, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x32, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x32, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x32, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x30, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x33, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x32, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x33, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x33, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x39, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x34, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x34, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x34,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x36, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x34, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x38, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x34, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x35, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x35, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x35, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x36, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x36, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x37, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x31, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x37, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x37, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x36,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x38, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x37, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x38, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x38, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x38, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x39, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x39, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x39, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x37, 0x00, 0x00
	};

	static uint8_t gtavc_menu_script[] = {
		0xA4, 0x03, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x00, 0x00, 0x00, 0xE5, 0x03, 0x43, 0x4C, 0x44, 0x53,
		0x43, 0x4C, 0x00, 0x00, 0x01, 0x00, 0x05, 0xD0, 0x07, 0xF0, 0x0D, 0xEE, 0x0D, 0x03, 0x0C, 0x00,
		0x03, 0x0D, 0x00, 0x01, 0x00, 0x04, 0x00, 0xDD, 0x0D, 0x03, 0x00, 0x00, 0x04, 0x00, 0xD6, 0x00,
		0x04, 0x15, 0x39, 0x00, 0x03, 0x00, 0x00, 0x04, 0x01, 0x56, 0x82, 0x02, 0xBC, 0x04, 0x4D, 0x00,
		0x01, 0xB4, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xB1, 0xFE, 0xFF, 0xFF, 0xE1, 0x0D, 0x03, 0x02,
		0x00, 0x04, 0x04, 0x04, 0x06, 0x04, 0x00, 0x05, 0xDC, 0x05, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00,
		0x03, 0x02, 0x00, 0x04, 0x00, 0x4D, 0x00, 0x01, 0x8D, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xB1,
		0xFE, 0xFF, 0xFF, 0xDC, 0x0D, 0x04, 0x00, 0x04, 0x01, 0xF1, 0x0D, 0xD0, 0x0D, 0x03, 0x00, 0x00,
		0x01, 0xAA, 0xFE, 0xFF, 0xFF, 0xF2, 0x0D, 0x03, 0x00, 0x00, 0x03, 0x0C, 0x00, 0xF5, 0x0D, 0x03,
		0x0B, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x0C, 0x00, 0x04, 0x00, 0x4D, 0x00, 0x01,
		0x4C, 0xFF, 0xFF, 0xFF, 0xE6, 0x03, 0x01, 0x00, 0x04, 0x64, 0xE5, 0x03, 0x43, 0x4C, 0x4D, 0x4E,
		0x55, 0x4E, 0x00, 0x00, 0xB4, 0x01, 0x02, 0xBC, 0x04, 0x04, 0x00, 0x01, 0x00, 0x04, 0x32, 0x73,
		0x03, 0x01, 0x00, 0x04, 0x00, 0xF4, 0x0D, 0x03, 0x0A, 0x00, 0x04, 0x64, 0xD6, 0x00, 0x04, 0x01,
		0x29, 0x00, 0x03, 0x0A, 0x00, 0x04, 0x00, 0x2D, 0x80, 0x03, 0x0A, 0x00, 0x03, 0x0C, 0x00, 0x4D,
		0x00, 0x01, 0xE9, 0xFE, 0xFF, 0xFF, 0xE6, 0x03, 0x01, 0x00, 0x04, 0x64, 0xEF, 0x0D, 0x03, 0x00,
		0x00, 0x03, 0x0A, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x00, 0x00, 0x04, 0x02, 0x4D,
		0x00, 0x01, 0xF0, 0xFE, 0xFF, 0xFF, 0xE5, 0x03, 0x43, 0x4C, 0x4D, 0x4E, 0x55, 0x31, 0x00, 0x00,
		0x02, 0x00, 0x01, 0xC5, 0xFE, 0xFF, 0xFF, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x0A, 0x00,
		0x04, 0xFE, 0x4D, 0x00, 0x01, 0xCC, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x64, 0x02, 0x00, 0x01,
		0xC5, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x3F, 0xFF, 0xFF, 0xFF, 0xF6, 0x0D, 0x03, 0x0B, 0x00,
		0xF3, 0x0D, 0xB4, 0x01, 0x02, 0xBC, 0x04, 0x04, 0x01, 0xDC, 0x0D, 0x04, 0x00, 0x04, 0x00, 0x02,
		0x00, 0x01, 0xDD, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x43, 0x4C, 0x45, 0x4F, 0x20, 0x4D,
		0x45, 0x4E, 0x55, 0x00, 0x43, 0x4C, 0x4F, 0x53, 0x45, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x30, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x31, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x31, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x32, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x32, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x32, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x33, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x33, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x33, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x30, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x34, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x32, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x34, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x34, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x39, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x35, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x35, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x34,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x36, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x35, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x38, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x35, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x36, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x36, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x36, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x37, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x37, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x38, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x31, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x38, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x38, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x36,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x38, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x38, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x39, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x39, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x39, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x30, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x30, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x30, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x30, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x37, 0x00, 0x00
	};

	static uint8_t sa_menu_script[] = {
		0xA4, 0x03, 0x09, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x00, 0x00, 0x00, 0xE5, 0x03, 0x09, 0x43, 0x4C,
		0x44, 0x53, 0x43, 0x00, 0x00, 0x00, 0x01, 0x00, 0x05, 0xB8, 0x0B, 0xF0, 0x0D, 0xEE, 0x0D, 0x03,
		0x0C, 0x00, 0x03, 0x0D, 0x00, 0x01, 0x00, 0x04, 0x00, 0xDD, 0x0D, 0x03, 0x00, 0x00, 0x04, 0x00,
		0xD6, 0x00, 0x04, 0x15, 0x39, 0x00, 0x03, 0x00, 0x00, 0x04, 0x01, 0x56, 0x82, 0x02, 0x08, 0x00,
		0x4D, 0x00, 0x01, 0xB2, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xAD, 0xFE, 0xFF, 0xFF, 0xE1, 0x0D,
		0x03, 0x02, 0x00, 0x04, 0x04, 0x04, 0x06, 0x04, 0x00, 0x05, 0xDC, 0x05, 0xD6, 0x00, 0x04, 0x00,
		0x39, 0x00, 0x03, 0x02, 0x00, 0x04, 0x00, 0x4D, 0x00, 0x01, 0x8B, 0xFF, 0xFF, 0xFF, 0x02, 0x00,
		0x01, 0xAD, 0xFE, 0xFF, 0xFF, 0xDC, 0x0D, 0x04, 0x00, 0x04, 0x01, 0xF1, 0x0D, 0xD0, 0x0D, 0x03,
		0x00, 0x00, 0x01, 0xA6, 0xFE, 0xFF, 0xFF, 0xF2, 0x0D, 0x03, 0x00, 0x00, 0x03, 0x0C, 0x00, 0xF5,
		0x0D, 0x03, 0x0B, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x0C, 0x00, 0x04, 0x00, 0x4D,
		0x00, 0x01, 0x49, 0xFF, 0xFF, 0xFF, 0xE6, 0x03, 0x01, 0x00, 0x04, 0x64, 0xE5, 0x03, 0x09, 0x43,
		0x4C, 0x4D, 0x4E, 0x55, 0x4E, 0x00, 0x00, 0xB4, 0x01, 0x02, 0x08, 0x00, 0x04, 0x00, 0x01, 0x00,
		0x04, 0x32, 0x73, 0x03, 0x01, 0x00, 0x04, 0x00, 0xF4, 0x0D, 0x03, 0x0A, 0x00, 0x04, 0x64, 0xD6,
		0x00, 0x04, 0x01, 0x29, 0x00, 0x03, 0x0A, 0x00, 0x04, 0x00, 0x2D, 0x80, 0x03, 0x0A, 0x00, 0x03,
		0x0C, 0x00, 0x4D, 0x00, 0x01, 0xE5, 0xFE, 0xFF, 0xFF, 0xE6, 0x03, 0x01, 0x00, 0x04, 0x64, 0xEF,
		0x0D, 0x03, 0x00, 0x00, 0x03, 0x0A, 0x00, 0xD6, 0x00, 0x04, 0x00, 0x39, 0x00, 0x03, 0x00, 0x00,
		0x04, 0x02, 0x4D, 0x00, 0x01, 0xEC, 0xFE, 0xFF, 0xFF, 0xE5, 0x03, 0x09, 0x43, 0x4C, 0x4D, 0x4E,
		0x55, 0x31, 0x00, 0x00, 0x02, 0x00, 0x01, 0xC1, 0xFE, 0xFF, 0xFF, 0xD6, 0x00, 0x04, 0x00, 0x39,
		0x00, 0x03, 0x0A, 0x00, 0x04, 0xFE, 0x4D, 0x00, 0x01, 0xC8, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x04,
		0x64, 0x02, 0x00, 0x01, 0xC1, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x3C, 0xFF, 0xFF, 0xFF, 0xF6,
		0x0D, 0x03, 0x0B, 0x00, 0xF3, 0x0D, 0xB4, 0x01, 0x02, 0x08, 0x00, 0x04, 0x01, 0xDC, 0x0D, 0x04,
		0x00, 0x04, 0x00, 0x02, 0x00, 0x01, 0xDB, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x43, 0x4C,
		0x45, 0x4F, 0x20, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x43, 0x4C, 0x4F, 0x53, 0x45, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x31, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x31, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x32, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x31, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x32, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x32, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x36,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x38, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x32, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x33, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x33, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x33, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x34, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x34, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x34, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x35, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x35, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x35, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x30, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x36, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x32, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x36, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x36, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x39, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x37, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x37, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x34,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x36, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x37, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x38, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x37, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x38, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x38, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x38, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x39, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x39, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x37, 0x00,
		0x00
	};

#endif

	static uint8_t lcs_menu_script[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA9, 0x03, 0x4D, 0x45, 0x4E, 0x55, 0x00, 0x00,
		0x29, 0x08, 0xD5, 0x0D, 0x0C, 0xDB, 0x00, 0x01, 0x39, 0x00, 0x0C, 0x07, 0x01, 0x4D, 0x00, 0x01,
		0xD3, 0xFF, 0xFF, 0xFF, 0xEA, 0x03, 0x43, 0x4C, 0x44, 0x53, 0x43, 0x00, 0x48, 0x08, 0x02, 0x00,
		0x01, 0xC9, 0xFF, 0xFF, 0xFF, 0xEA, 0x03, 0x43, 0x4C, 0x44, 0x53, 0x43, 0x4C, 0x00, 0x00, 0x01,
		0x00, 0x08, 0xD0, 0x07, 0xF0, 0x0D, 0xEE, 0x0D, 0x18, 0x0C, 0x01, 0x00, 0x01, 0xD5, 0x0D, 0x0C,
		0xDB, 0x00, 0x01, 0x39, 0x00, 0x0C, 0x07, 0x01, 0x4D, 0x00, 0x01, 0x9D, 0xFF, 0xFF, 0xFF, 0x8B,
		0x00, 0x20, 0xCE, 0x19, 0x02, 0x00, 0x01, 0x98, 0xFF, 0xFF, 0xFF, 0x8B, 0x00, 0x20, 0xCE, 0x18,
		0xDD, 0x0D, 0x0C, 0x01, 0xDB, 0x00, 0x01, 0x39, 0x00, 0x0C, 0x07, 0x01, 0x4D, 0x00, 0x01, 0x7E,
		0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x9B, 0xFE, 0xFF, 0xFF, 0xE1, 0x0D, 0x0D, 0x07, 0x04, 0x07,
		0x06, 0x01, 0x08, 0xDC, 0x05, 0xE2, 0x0D, 0x0E, 0xDB, 0x00, 0x07, 0x02, 0x39, 0x00, 0x0D, 0x01,
		0x39, 0x00, 0x0E, 0x01, 0x4D, 0x00, 0x01, 0x56, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x9B, 0xFE,
		0xFF, 0xFF, 0xDC, 0x0D, 0x01, 0x07, 0x01, 0xF1, 0x0D, 0xD0, 0x0D, 0x0C, 0x06, 0x94, 0xFE, 0xFF,
		0xFF, 0xF2, 0x0D, 0x0C, 0x18, 0xF5, 0x0D, 0x17, 0xD5, 0x0D, 0x0C, 0xDB, 0x00, 0x07, 0x02, 0x39,
		0x00, 0x0C, 0x07, 0x01, 0x39, 0x00, 0x18, 0x01, 0x4D, 0x00, 0x01, 0x19, 0xFF, 0xFF, 0xFF, 0xEB,
		0x03, 0x01, 0x00, 0x07, 0x64, 0xEA, 0x03, 0x43, 0x4C, 0x4D, 0x4E, 0x55, 0x4E, 0x00, 0x00, 0xB9,
		0x01, 0x20, 0x01, 0x01, 0x00, 0x07, 0x32, 0x78, 0x03, 0x01, 0x00, 0x01, 0xF4, 0x0D, 0x16, 0x07,
		0x64, 0xDB, 0x00, 0x07, 0x02, 0x29, 0x00, 0x16, 0x01, 0x2D, 0x80, 0x16, 0x18, 0x4D, 0x00, 0x01,
		0xCA, 0xFE, 0xFF, 0xFF, 0xEB, 0x03, 0x01, 0x00, 0x07, 0x64, 0xEF, 0x0D, 0x0C, 0x16, 0xDB, 0x00,
		0x01, 0x39, 0x00, 0x0C, 0x07, 0x02, 0x4D, 0x00, 0x01, 0xD1, 0xFE, 0xFF, 0xFF, 0xEA, 0x03, 0x43,
		0x4C, 0x4D, 0x4E, 0x55, 0x31, 0x00, 0x00, 0x02, 0x00, 0x01, 0xA9, 0xFE, 0xFF, 0xFF, 0xDB, 0x00,
		0x01, 0x39, 0x00, 0x16, 0x07, 0xFE, 0x4D, 0x00, 0x01, 0xB0, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x07,
		0x64, 0x02, 0x00, 0x01, 0xA9, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x0F, 0xFF, 0xFF, 0xFF, 0xF6,
		0x0D, 0x17, 0xF3, 0x0D, 0xB9, 0x01, 0x20, 0x07, 0x01, 0xDC, 0x0D, 0x01, 0x01, 0x02, 0x00, 0x01,
		0xBE, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x43, 0x4C, 0x45, 0x4F, 0x20, 0x4D, 0x45, 0x4E,
		0x55, 0x00, 0x43, 0x4C, 0x4F, 0x53, 0x45, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x30, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x31, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x32, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x32, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x33, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x31, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x33, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x33, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x36,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x38, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x33, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x34, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x34, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x34, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x35, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x35, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x35, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x36, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x36, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x36, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x30, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x37, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x32, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x37, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x37, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x39, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x38, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x38, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x34,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x36, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x38, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x38, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x38, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x39, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x39, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x39, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30,
		0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x37, 0x00, 0x00
	};

#ifndef ANDROID

	static uint8_t vcs_menu_script[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x02, 0x0A, 0x4D, 0x45, 0x4E, 0x55, 0x00,
		0x67, 0x02, 0x0A, 0x43, 0x4C, 0x44, 0x53, 0x43, 0x00, 0x01, 0x00, 0x08, 0xD0, 0x07, 0xF0, 0x0D,
		0xEE, 0x0D, 0x19, 0x0D, 0x01, 0x00, 0x01, 0xD5, 0x0D, 0x0D, 0x78, 0x00, 0x01, 0x1B, 0x00, 0x0D,
		0x07, 0x01, 0x22, 0x00, 0x01, 0xC8, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xC3, 0xFF, 0xFF, 0xFF,
		0x04, 0x00, 0x21, 0xD0, 0x0E, 0xDD, 0x0D, 0x0D, 0x01, 0x78, 0x00, 0x01, 0x1B, 0x00, 0x0D, 0x07,
		0x01, 0x22, 0x00, 0x01, 0xA9, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0xED, 0xFE, 0xFF, 0xFF, 0xE1,
		0x0D, 0x0E, 0x07, 0x04, 0x07, 0x06, 0x01, 0x08, 0xDC, 0x05, 0xE2, 0x0D, 0x0F, 0x78, 0x00, 0x07,
		0x02, 0x1B, 0x00, 0x0E, 0x01, 0x1B, 0x00, 0x0F, 0x01, 0x22, 0x00, 0x01, 0x81, 0xFF, 0xFF, 0xFF,
		0x02, 0x00, 0x01, 0xED, 0xFE, 0xFF, 0xFF, 0xDC, 0x0D, 0x01, 0x07, 0x01, 0xF1, 0x0D, 0xD0, 0x0D,
		0x0D, 0x06, 0xE6, 0xFE, 0xFF, 0xFF, 0xF2, 0x0D, 0x0D, 0x19, 0xF5, 0x0D, 0x18, 0x07, 0x01, 0x21,
		0x01, 0x01, 0x00, 0x07, 0x32, 0x21, 0x02, 0x01, 0x00, 0x01, 0xF4, 0x0D, 0x17, 0x07, 0x64, 0x78,
		0x00, 0x07, 0x02, 0x15, 0x00, 0x17, 0x01, 0x17, 0x80, 0x17, 0x19, 0x22, 0x00, 0x01, 0x1C, 0xFF,
		0xFF, 0xFF, 0x68, 0x02, 0x01, 0x00, 0x07, 0x64, 0xEF, 0x0D, 0x0D, 0x17, 0x78, 0x00, 0x01, 0x1B,
		0x00, 0x0D, 0x07, 0x02, 0x22, 0x00, 0x01, 0x23, 0xFF, 0xFF, 0xFF, 0x67, 0x02, 0x0A, 0x43, 0x4C,
		0x4D, 0x4E, 0x55, 0x31, 0x00, 0x02, 0x00, 0x01, 0xFB, 0xFE, 0xFF, 0xFF, 0x78, 0x00, 0x01, 0x1B,
		0x00, 0x17, 0x07, 0xFE, 0x22, 0x00, 0x01, 0x02, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x64, 0x02,
		0x00, 0x01, 0xFB, 0xFE, 0xFF, 0xFF, 0x02, 0x00, 0x01, 0x61, 0xFF, 0xFF, 0xFF, 0xF6, 0x0D, 0x18,
		0xF3, 0x0D, 0x07, 0x01, 0x21, 0x07, 0x01, 0xDC, 0x0D, 0x01, 0x01, 0x02, 0x00, 0x01, 0xE4, 0xFF,
		0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x43, 0x4C, 0x45, 0x4F, 0x20, 0x4D, 0x45, 0x4E, 0x55, 0x00,
		0x43, 0x4C, 0x4F, 0x53, 0x45, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x31, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x31, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x30, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x32, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x32, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x32, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32,
		0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x37, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x32, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x32, 0x39, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x33, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x33, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x34,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x36, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x33, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x33, 0x38, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x33, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34,
		0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x33, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x34, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x35, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x34, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x34, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x34, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x30,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x32, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x35, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x34, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x35, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35,
		0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x35, 0x39, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x36, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x31, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x36, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x36, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x36,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x36, 0x38, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x36, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x30, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x37, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37,
		0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x35, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x37, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x37, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x37, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x37, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x38, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x32,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x34, 0x00, 0x43,
		0x53, 0x49, 0x5F, 0x38, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x36, 0x00, 0x43, 0x53, 0x49,
		0x5F, 0x38, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38, 0x38, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x38,
		0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x30, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x31, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x39, 0x32, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x33, 0x00, 0x43, 0x53,
		0x49, 0x5F, 0x39, 0x34, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F,
		0x39, 0x36, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x37, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x38,
		0x00, 0x43, 0x53, 0x49, 0x5F, 0x39, 0x39, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x30, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x31, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x32, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x33, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x34, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x35, 0x00, 0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x36, 0x00,
		0x43, 0x53, 0x49, 0x5F, 0x31, 0x30, 0x37, 0x00, 0x00
	};

#endif
}