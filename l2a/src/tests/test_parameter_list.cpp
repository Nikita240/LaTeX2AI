// -----------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2020 Ivo Steinbrecher (https://github.com/stoani89/LaTeX2AI)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// -----------------------------------------------------------------------------

/**
 * \brief Test the parameter list class.
 */


#include "IllustratorSDK.h"
#include "test_parameter_list.h"

#include "test_utlity.h"
#include "../utility/parameter_list.h"


/**
 *
 */
void L2A::TEST::TestParameterList(L2A::TEST::UTIL::UnitTest& ut)
{
    // Set test name.
    ut.SetTestName(ai::UnicodeString("ParameterList"));

    // Populate a parameter list.
    L2A::UTIL::ParameterList first_list;
    first_list.SetOption(ai::UnicodeString("key0"), ai::UnicodeString("bad_value"));
    first_list.SetOption(ai::UnicodeString("key0"), ai::UnicodeString("value0"));
    first_list.SetOption(ai::UnicodeString("key1"), ai::UnicodeString("value1"));
    first_list.SetOption(ai::UnicodeString("key2"), 2);
    first_list.SetOption(ai::UnicodeString("key3"), ai::UnicodeString("Umlaute ������@!\nund neue Zeile"));
    first_list.SetOption(ai::UnicodeString("text"),
        ai::UnicodeString("Hier ist ein langer Text mit Umlauten ������@!\nund neue Zeilen\n\n\nthe end<>/''\"!\n"));

    // Add sub list.
    L2A::UTIL::ParameterList sub_list;
    sub_list.SetOption(ai::UnicodeString("subkey0"), ai::UnicodeString("bad_value"));
    sub_list.SetOption(ai::UnicodeString("subkey0"), ai::UnicodeString("0"));
    ai::UnicodeString main_text("    \n    \n    \n    \nMainOptionText\n    \n    \n");
    sub_list.SetMainOption(main_text);
    first_list.SetSubList(ai::UnicodeString("sublist_key0"), sub_list);

    // Add second sub list.
    std::shared_ptr<L2A::UTIL::ParameterList> sub_list_2 = first_list.SetSubList(ai::UnicodeString("sublist_key1"));
    sub_list_2->SetMainOption(
        ai::UnicodeString("Hier ist ein langer Text mit Umlauten ������@!\nund neue Zeilen\n\n\nthe end<>/''\"!\n"));
    sub_list_2->SetOption(ai::UnicodeString("key0"), ai::UnicodeString("newvalue"));

    // Transform this list to a string and read it again.
    L2A::UTIL::ParameterList transformed_list(first_list.ToXMLString(ai::UnicodeString("root")));

    // Check the results.
    ut.CompareStr(transformed_list.GetStringOption(ai::UnicodeString("key0")), ai::UnicodeString("value0"));
    ut.CompareStr(transformed_list.GetStringOption(ai::UnicodeString("key1")), ai::UnicodeString("value1"));
    ut.CompareStr(transformed_list.GetStringOption(ai::UnicodeString("key2")), ai::UnicodeString("2"));
    ut.CompareInt(2, transformed_list.GetIntOption(ai::UnicodeString("key2")));
    ut.CompareStr(transformed_list.GetStringOption(ai::UnicodeString("key3")),
        ai::UnicodeString("Umlaute ������@!\nund neue Zeile"));
    ut.CompareStr(transformed_list.GetStringOption(ai::UnicodeString("text")),
        ai::UnicodeString("Hier ist ein langer Text mit Umlauten ������@!\nund neue Zeilen\n\n\nthe end<>/''\"!\n"));
    ut.CompareStr(
        transformed_list.GetSubList(ai::UnicodeString("sublist_key0"))->GetStringOption(ai::UnicodeString("subkey0")),
        ai::UnicodeString("0"));
    ut.CompareStr(transformed_list.GetSubList(ai::UnicodeString("sublist_key0"))->GetMainOption(), main_text);
    ut.CompareStr(transformed_list.GetSubList(ai::UnicodeString("sublist_key1"))->GetMainOption(),
        ai::UnicodeString("Hier ist ein langer Text mit Umlauten ������@!\nund neue Zeilen\n\n\nthe end<>/''\"!\n"));
    ut.CompareStr(
        transformed_list.GetSubList(ai::UnicodeString("sublist_key1"))->GetStringOption(ai::UnicodeString("key0")),
        ai::UnicodeString("newvalue"));

    // Change some options in a sublist and check that the smart pointer works correctly.
    std::shared_ptr<L2A::UTIL::ParameterList> sub_list_ptr =
        transformed_list.GetSubListMutable(ai::UnicodeString("sublist_key0"));
    sub_list_ptr->SetOption(ai::UnicodeString("subkey0"), 666);
    ut.CompareStr(
        transformed_list.GetSubList(ai::UnicodeString("sublist_key0"))->GetStringOption(ai::UnicodeString("subkey0")),
        ai::UnicodeString("666"));
}