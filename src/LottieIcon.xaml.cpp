#include "pch.h"

#include "LottieIcon.xaml.h"
#if __has_include("LottieIcon.g.cpp")
#include "LottieIcon.g.cpp"
#endif
#include "winrt/Windows.UI.Xaml.Media.Animation.h"

#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::CppWinUIGallery::implementation
{
bool isPressedState = false;

int32_t LottieIcon::MyProperty()
{
    throw hresult_not_implemented();
}

void LottieIcon::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void LottieIcon::LottieButton_Click(IInspectable const &sender, RoutedEventArgs const &e)
{

    if (LottieButton().IsChecked().GetBoolean() == true)
    {
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
        return;
    }
    else
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
    return;
}
void LottieIcon::Button_PointerEntered(IInspectable const &sender, PointerRoutedEventArgs const &e)
{
    //    if (!isPressedState)
    if (LottieButton().IsChecked().GetBoolean() == true)
        return;
    else
    {

        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"PointerOver");
        return;
    }
}

// Handle pointer exiting the button area
void LottieIcon::Button_PointerExited(IInspectable const &sender, PointerRoutedEventArgs const &e)
{
    if (LottieButton().IsChecked().GetBoolean() == false)
    {
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
    }
    else
    {
        AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
        return;
    }
}
void LottieIcon::InitializeIconState()
{
    IconSource().Color_000000(Windows::UI::Colors::Transparent());
    IconSource().Color_FFFFFF(Windows::UI::Colors::Transparent());

    AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
}
void LottieIcon::LottieButton_Loaded(IInspectable const &sender, RoutedEventArgs const &e)
{
    InitializeIconState();
}

} // namespace winrt::CppWinUIGallery::implementation

void winrt::CppWinUIGallery::implementation::LottieIcon::LottieButtonTransparent_Click(
    winrt::Windows::Foundation::IInspectable const &sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    if (LottieButtonTransparent().IsChecked().GetBoolean() == false)
    {
        IconSource().Color_FFD640(Windows::UI::Colors::Yellow());
    }
    else
    {
        IconSource().Color_FFD640(Windows::UI::Colors::Blue());

        return;
    }
}

void winrt::CppWinUIGallery::implementation::LottieIcon::SourceCodeTextBox_Loaded(
    winrt::Windows::Foundation::IInspectable const &sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{

    auto textBox = SourceCodeTextBox();

    hstring xamlSourceCode = LR"(
<ToggleButton Loaded="LottieButton_Loaded"  Width="75" IsEnabled="True" x:Name="LottieButton" Margin="0,10,0,10"  Click="LottieButton_Click" PointerExited="Button_PointerExited" PointerEntered="Button_PointerEntered">
                   

                    <AnimatedIcon x:Name="SearchAnimatedIcon">
                        <AnimatedIcon.Source>
                            <local:AnimatedLogo/>
                        </AnimatedIcon.Source>
                        <AnimatedIcon.FallbackIconSource>
                            <SymbolIconSource Symbol="GlobalNavigationButton"/>
                        </AnimatedIcon.FallbackIconSource>
                    </AnimatedIcon>
                </ToggleButton>
)";
    textBox.Text(xamlSourceCode);
}

void winrt::CppWinUIGallery::implementation::LottieIcon::CppCodeTextBox_Loaded(
    winrt::Windows::Foundation::IInspectable const &sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    auto textBox = CppCodeTextBox();
    hstring cppSourceCode = LR"(
 void LottieIcon::LottieButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {


        if (LottieButton().IsChecked().GetBoolean() == true)
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
            return;
        }
        else
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
        return;

    }
    void LottieIcon::Button_PointerEntered(IInspectable const& sender, PointerRoutedEventArgs const& e)
    {
    //    if (!isPressedState)
        if (LottieButton().IsChecked().GetBoolean() == true)
            return;
        else
        {

            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"PointerOver");
            return;
        }
    }

    // Handle pointer exiting the button area
    void LottieIcon::Button_PointerExited(IInspectable const& sender, PointerRoutedEventArgs const& e)
    {
        if (LottieButton().IsChecked().GetBoolean() == false
            )
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
        }
        else
        {
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Pressed");
            return;
        }
    }
    void LottieIcon::InitializeIconState()
    {
       
            AnimatedIcon::SetState(this->SearchAnimatedIcon(), L"Normal");
    }
    void LottieIcon::LottieButton_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        InitializeIconState();
    }

)";
    textBox.Text(cppSourceCode);
}
