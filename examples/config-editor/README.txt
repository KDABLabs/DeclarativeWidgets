This example demonstrates runtime loading of UI that was not provided by the application vendor.

The application is a simple configuration editor which can either load configuration files as text,
or, if there is a QML file with a matching name in the same directory or a standard data location,
allow editing through the custom UI provided by that QML file.

The demodata directory contains a simple configuration file with suitable DeclarativeWidget based
custom editor.
The program in question can be configured for one of three database backends, each with its own options.
