//
//  Global.h
//
//  Created by ryoheikomiyama on 2017/05/05.
//
//
#pragma once

// meter or centimeter
#define METERSCALE
#ifdef METERSCALE
#define SCALE 100.0
#else
#define SCALE 1.0
#endif

// 1 or 255
#define COLOR1
#ifdef COLOR1
#define COLORSCALE 255.0
#else
#define COLORSCALE 1.0
#endif
