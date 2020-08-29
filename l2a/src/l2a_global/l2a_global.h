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
 * \brief A global object for L2A to store parameters.
 */


#ifndef L2A_GLOBAL_H_
#define L2A_GLOBAL_H_


// Forward declarations.
namespace L2A
{
    namespace UTIL
    {
        class ParameterList;
    }
}  // namespace L2A


namespace L2A
{
    namespace GLOBAL
    {
        /**
         * \brief Class for the global object.
         */
        class Global
        {
           public:
            /**
             * \brief Empty constructor.
             */
            Global() : is_setup_(false), is_testing_(false){};

            /**
             * \brief Destructor. Here the options will be stored in an application file.
             */
            ~Global();

            /**
             * \brief Set up the global variables.
             */
            void SetUp();

            /**
             * \brief Return true if the object could be setup correctly.
             */
            inline bool IsSetup() const { return is_setup_; }

            /**
             * \brief Open a form and let the user select some global options.
             **/
            void SetFromUserForm();

            /**
             * \brief Set the values for this object from a xml string.
             */
            ai::UnicodeString GetLatexCommand() const;

           private:
            /**
             * \brief Convert this object to a parameter list.
             */
            void ToParameterList(std::shared_ptr<L2A::UTIL::ParameterList>& parameter_list) const;

            /**
             * \brief Convert this object to a xml string.
             */
            ai::UnicodeString ToString() const;

            /**
             * \brief Get a parameter list with the default options.
             */
            void GetDefaultParameterList(std::shared_ptr<L2A::UTIL::ParameterList>& parameter_list) const;

            /**
             * \brief Set the values for this object from a parameter list.
             */
            void SetFromParameterList(const L2A::UTIL::ParameterList& parameter_list);

           public:
            //! Flag if item could be setup.
            bool is_setup_;

            //! Path to the latex executables.
            ai::FilePath path_latex_;

            //! Command for latex in the shell.
            ai::UnicodeString command_latex_;

            //! Options for the latex command.
            ai::UnicodeString command_latex_options_;

            //! Command for ghostscript in the shell.
            ai::UnicodeString command_gs_;

            //! Path to temp folder.
            ai::FilePath path_temp_;

            //! Path to form exe.
            ai::FilePath path_form_exe_;

            //! Path to application data directory.
            ai::FilePath application_data_directory_;

            //! File that stores global application data.
            ai::FilePath application_data_path_;

            //! File that stores last item input.
            ai::FilePath l2a_item_last_input_;

            //! Flag if testing is currently active.
            bool is_testing_;

            //! Parameter list that will be returned for forms during testing.
            std::shared_ptr<L2A::UTIL::ParameterList> testing_form_return_parameter_list_;
        };

        void CheckGlobal();

        /**
         * \brief Define global instance of Global, this object should not be used, only accessed via the Get
         * functions.
         */
        extern Global* _l2a_global;

    }  // namespace GLOBAL

    /**
     * \brief Return the global object.
     */
    const L2A::GLOBAL::Global& Global();

    /**
     * \brief Return the global object mutable.
     */
    L2A::GLOBAL::Global& GlobalMutable();

}  // namespace L2A

#endif
