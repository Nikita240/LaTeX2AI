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
 * \brief Errors for l2a applications.
 */


#ifndef L2A_ERROR_H_
#define L2A_ERROR_H_


namespace L2A
{
    namespace ERR
    {
        /**
         * \brief Base class for L2A Errors.
         */
        class Exception : public exception
        {
           public:
            /**
             * \brief Constructor with error string.
             */
            Exception(const ai::UnicodeString& error_string) : exception(), error_string_(error_string)
            {
#ifdef _DEBUG
                // In debug show all exceptions that happen.
                sAIUser->MessageAlert(error_string_);
#endif
            }

           protected:
            //! String containing information regarding this error.
            ai::UnicodeString error_string_;
        };

        /**
         * \brief Check if illustrator returned a non zero exit status.
         */
        inline void check_ai_error(AIErr err)
        {
            if (err) throw Exception(ai::UnicodeString("Ilustrator Error"));
        }
    }  // namespace ERR
}  // namespace L2A

#endif