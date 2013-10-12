// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVOB_LEVELEDITOR_JSON
#define SSVOB_LEVELEDITOR_JSON

#include "SSVBloodshed/OBCommon.h"
#include "SSVBloodshed/LevelEditor/OBLESector.h"
#include "SSVBloodshed/LevelEditor/OBLELevel.h"
#include "SSVBloodshed/LevelEditor/OBLETile.h"

namespace ssvuj
{
	template<> struct Converter<ob::OBLETType>
	{
		using T = ob::OBLETType;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ ssvuj::extrEnum<T, int>(mObj, mValue); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ ssvuj::archEnum<T, int>(mObj, mValue); }
	};

	template<> struct Converter<ob::OBLETile>
	{
		using T = ob::OBLETile;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ ssvuj::extrArray(mObj, mValue.x, mValue.y, mValue.z, mValue.type, mValue.params); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ ssvuj::archArray(mObj, mValue.x, mValue.y, mValue.z, mValue.type, mValue.params); }
	};

	template<> struct Converter<ob::OBLELevel>
	{
		using T = ob::OBLELevel;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ ssvuj::extrArray(mObj, mValue.x, mValue.y, mValue.columns, mValue.rows, mValue.depth, mValue.tiles); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ ssvuj::archArray(mObj, mValue.x, mValue.y, mValue.columns, mValue.rows, mValue.depth, mValue.getTilesNonNull()); }
	};

	template<> struct Converter<ob::OBLESector>
	{
		using T = ob::OBLESector;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ ssvuj::extr(mObj, mValue.levels); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ ssvuj::arch(mObj, mValue.levels); }
	};
}

#endif
