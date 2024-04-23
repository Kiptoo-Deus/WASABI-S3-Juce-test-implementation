#include <JuceHeader.h>
#include "MainComponent.h"
#include "AuthenticationComponent.h"

//==============================================================================
class WASABIJucetestimplementationApplication : public juce::JUCEApplication
{
public:
    WASABIJucetestimplementationApplication() {}

    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String& commandLine) override
    {
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted(const juce::String& commandLine) override {}

    class MainWindow : public juce::DocumentWindow, public AuthenticationListener
    {
    public:
        MainWindow(juce::String name)
            : DocumentWindow(name,
                juce::Desktop::getInstance().getDefaultLookAndFeel()
                .findColour(juce::ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);

            // Create an instance of AuthenticationComponent
            authenticationComponent.reset(new AuthenticationComponent());
            authenticationComponent->setListener(this); // Set this class as the listener for authentication events
            setContentOwned(authenticationComponent.get(), true); // Set AuthenticationComponent as the content

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
#endif

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        // Implement the authenticationSubmitted method from AuthenticationListener
        void authenticationSubmitted(const juce::String& clubName, const juce::String& region) override
        {
            // Remove the authentication component
            setContentOwned(new MainComponent(), true); // Set MainComponent as the content
        }

    private:
        std::unique_ptr<AuthenticationComponent> authenticationComponent;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(WASABIJucetestimplementationApplication)
