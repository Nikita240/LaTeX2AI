// -----------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2020 Ivo Steinbrecher
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
 * \brief Errors for l2a applications.
 */


#include "IllustratorSDK.h"
#include "l2a_error.h"

#include "utility/string_functions.h"


#ifdef _DEBUG
#include "../../tpl/StackWalker/Main/StackWalker/StackWalker.h"

/**
 * \brief User class to obtain a vector with the current stack.
 */
class MyStackWalker : public StackWalker
{
   public:
    /**
     * \brief Constructor.
     */
    MyStackWalker() : StackWalker(), stack_lines_() {}

    /**
     * \brief Return a string with the stack information.
     */
    ai::UnicodeString GetStack() const
    {
        ai::UnicodeString stack_string("");
        for (unsigned int i = 0; i < stack_lines_.size(); i++)
        {
            stack_string += stack_lines_[i];
            if (i < stack_lines_.size() - 1) stack_string += "\n";
        }
        return stack_string;
    }

   protected:
    /**
     * \brief This method is called for each line in the stack.
     *
     * Here we check if the line is of interest to us and save it in the stack vector.
     */
    virtual void OnOutput(LPCSTR szText)
    {
        std::string stack_line(szText);
        if (stack_line.find("latex2ai") != std::string::npos && stack_line.find("StackWalker") == std::string::npos)
            stack_lines_.push_back(ai::UnicodeString(szText));
    }

   private:
    //! Vector with the relevant stack lines.
    std::vector<ai::UnicodeString> stack_lines_;
};
#endif

/**
 *
 */
L2A::ERR::Exception::Exception(
    const char* __file__, const int __line__, const char* __function__, const ai::UnicodeString& error_string)
    : ExceptionBase()
{
    ai::UnicodeString full_error_string(
        "--------------------------------------------------------------------------------\n");
    full_error_string += "LaTeX2AI Error! If this happens, please open an issue under\n";
    full_error_string += "github.com/stoani89/LaTeX2AI/issues\n";
    full_error_string += "--------------------------------------------------------------------------------\n";
#ifdef _DEBUG
    full_error_string += "Stack:\n";
    full_error_string += "--------------------------------------------------------------------------------\n";
    MyStackWalker sw;
    sw.ShowCallstack();
    full_error_string += sw.GetStack();
    full_error_string += "\n--------------------------------------------------------------------------------\n";
#endif
    full_error_string += "Error thrown at:\n";
    full_error_string += "--------------------------------------------------------------------------------\n";
    full_error_string += ai::UnicodeString(__file__);
    full_error_string += "::";
    char buff[100];
    snprintf(buff, sizeof(buff), "%d", __line__);
    full_error_string += ai::UnicodeString(buff);
    full_error_string += "\n";
    full_error_string += ai::UnicodeString(__function__);
    full_error_string += "\n--------------------------------------------------------------------------------\n\n";
    full_error_string += error_string;
    sAIUser->MessageAlert(full_error_string);
}
