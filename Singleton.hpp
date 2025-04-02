/*
*************************************************************
*                                                           *
*   Flowhooks Software - Open Source License                *
*                                                           *
*  This software is licensed under the GNU Affero General   *
*  Public License v3. You may use, modify, and distribute   *
*  this code under the terms of the AGPLv3.                 *
*                                                           *
*  This program is distributed in the hope that it will be  *
*  useful, but WITHOUT ANY WARRANTY; without even the       *
*  implied warranty of MERCHANTABILITY or FITNESS FOR A     *
*  PARTICULAR PURPOSE. See the GNU AGPLv3 for more details. *
*                                                           *
*  Author: Felipe Cezar Paz (git@felipecezar.com)           *
*  File:                                                    *
*  Description: FlowHooks Graphical User Interface (FHGUI)  *
*                                                           *
*************************************************************
*/

#pragma once

template<typename T>
class Singleton
{
protected:
    Singleton() {}
    ~Singleton() {}

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

public:
    static T& Get()
    {
        static T inst{};
        return inst;
    }
};