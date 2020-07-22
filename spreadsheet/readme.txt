This spreadsheet is for analyzing the CubeSat Simulator telemetry.

This is only used for the AFSK 1200 APRS telemetry mode.  The latest version of the CubeSatSim supports Fox-1 telemetry emulation, so the use of this mode is encouraged - it does not use this spreadsheet as the telemetry is automatically decoded and graphed.

Setting up FoxTelem is described here https://github.com/alanbjohnston/CubeSatSim/wiki/Ground-Station

This spreadsheet has been tested with Office 365 (Windows) and Office Excel for Mac (Version: 16.16.6) and LibreOffice Calc Version: 6.1.4.2 (Windows)

A version for Google Docs is available for copying and download at:

 http://cubesatsim.org/telem

Instructions:

Copy your raw telemetry data into the Data Input tab.  If you don't have any data, copy data from the Sample Data tab.

The odd rows should be a time timestamp (which is ignored) while the even rows should contain frames of telemetry data (beginning with "hi hi" then a series of 3 digit numbers).  If this isn't the case, you will need to edit until even lines starting at row 2 contain frames of telemetry.

The telemetry starting in Row 2 will be automatically calculated and plotted.

See plots in Voltage Graphs, Current Graphs, and Temperature Graph tabs.

To see raw data or create a new plot, go to Graphs tab
