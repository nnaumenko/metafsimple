# C++ library for processing and simplifying weather data obtained from METAR and TAF reports

[![pipeline status](https://gitlab.com/nnaumenko/metafsimple/badges/master/pipeline.svg)](https://gitlab.com/nnaumenko/metafsimple/-/commits/master)
[![codecov](https://codecov.io/gh/nnaumenko/metafsimple/branch/master/graph/badge.svg)](https://codecov.io/gh/nnaumenko/metafsimple)

The purpose of this library is to collate and organise the data produced by
parsing METAR or TAF report with Metaf library (available on [gitlab](https://gitlab.com/nnaumenko/metaf) or [github](https://github.com/nnaumenko/metaf).

This project is a work in progress.

The following example illustrates the principle.

<table>
<tr align=center>
<td colspan=2>
Report: <b>METAR UKLI 071600Z 28003MPS 250V330 9999 -SHRA BKN019CB BKN028 13/12 Q1015 NOSIG=</b>
</td>
</tr>
<tr align=center>
<td>Parsed by Metaf library</td>
<td>Simplified by MetafSimple</td>
</tr>
<tr valign=top>
<td>
metadata:<br>
&nbsp;&nbsp;type: METAR,<br>
&nbsp;&nbsp;report_time: {day: 7, hour: 16, minute: 0}<br>
&nbsp;&nbsp;icao_location: "UKLI"<br>
<br>
group[0]: KeywordGroup<br>
&nbsp;&nbsp;type: METAR<br>
<br>
group[1]: LocationGroup<br>
&nbsp;&nbsp;location: "UKLI"<br>
<br>
group[2]: ReportTimeGroup<br>
&nbsp;&nbsp;report_time: {day: 7, hour: 16, minute: 0}<br>
<br>
group[3]: WindGroup<br>
&nbsp;&nbsp;type: SURFACE_WIND_WITH_VARIABLE_SECTOR<br>
&nbsp;&nbsp;direction: {type: VALUE_DEGREES, degrees: 280}<br>
&nbsp;&nbsp;speed: {speed: 3, unit: KNOTS}<br>
&nbsp;&nbsp;varSectorBegin: {type: VALUE_DEGREES, degrees: 250}<br>
&nbsp;&nbsp;varSectorEnd: {type: VALUE_DEGREES, degrees: 330}<br>
<br>
groupinfo[4]: VisibilityGroup<br>
&nbsp;&nbsp;type: PREVAILING<br>
&nbsp;&nbsp;visibility: {modifier: MORE_THAN, distance: 10000, unit:METERS}<br>
<br>
groupinfo[5]: WeatherGroup<br>
&nbsp;&nbsp;type: CURRENT<br>
&nbsp;&nbsp;weatherPhenomena:<br>
&nbsp;&nbsp;&nbsp;&nbsp;qualifier: LIGHT<br>
&nbsp;&nbsp;&nbsp;&nbsp;descriptor: SHOWERS<br>
&nbsp;&nbsp;&nbsp;&nbsp;weather[0]: RAIN<br>
<br>
groupinfo[6]: CloudGroup<br>
&nbsp;&nbsp;type: CLOUD_LAYER<br>
&nbsp;&nbsp;amount: BROKEN<br>
&nbsp;&nbsp;height: {modifier: NONE, distance: 1900, unit: FEET}<br>
&nbsp;&nbsp;convectiveType: CUMULONIMBUS<br>
<br>
groupinfo[7]: CloudGroup<br>
&nbsp;&nbsp;type: CLOUD_LAYER<br>
&nbsp;&nbsp;amount: BROKEN<br>
&nbsp;&nbsp;height: {modifier: NONE, distance: 2800, unit: FEET}<br>
&nbsp;&nbsp;convectiveType: NONE<br>
<br>
groupinfo[8]: TemperatureGroup<br>
&nbsp;&nbsp;type: TEMPERATURE_DEW_POINT<br>
&nbsp;&nbsp;airTemperature: {temperature: 13, unit:C}<br>
&nbsp;&nbsp;dewPoint: {temperature: 12, unit:C}<br>
<br>
groupinfo[9]: PressureGroup<br>
&nbsp;&nbsp;type: QNH<br>
&nbsp;&nbsp;pressure: {pressure: 1015, unit:HECTOPASCAL}<br>
<br>
group[10]: TrendGroup<br>
&nbsp;&nbsp;type: NOSIG<br>
</td>
<td>
report:<br>
&nbsp;&nbsp;type: METAR<br>
&nbsp;&nbsp;reportTime: {day: 6, hour: 17, minute: 0}<br>
<br>
station:<br>
&nbsp;&nbsp;icaoCode: "UKLI"<br>
<br>
current:<br>
&nbsp;&nbsp;airTemperature: {temperature: 13, unit: C}<br>
&nbsp;&nbsp;dewPoint: {temperature: 12, unit: C}<br>
&nbsp;&nbsp;pressureSeaLevel: {pressure: 1015, unit: HPA}<br>
&nbsp;&nbsp;weatherData: <br>
&nbsp;&nbsp;&nbsp;&nbsp;windDirectionDegrees: 280<br>
&nbsp;&nbsp;&nbsp;&nbsp;windSpeed: {speed: 3, unit: MPS}<br>
&nbsp;&nbsp;&nbsp;&nbsp;windDirectionVarFromDegrees: 250<br>
&nbsp;&nbsp;&nbsp;&nbsp;windDirectionVarToDegrees: 330<br>
&nbsp;&nbsp;&nbsp;&nbsp;visibility: {details: MORE_THAN, distance: 10000, unit: METERS}<br>
&nbsp;&nbsp;&nbsp;&nbsp;skyCondition: CLOUDS<br>
&nbsp;&nbsp;&nbsp;&nbsp;cloudLayers[0]:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;amount: BROKEN<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;height: {height: 1900, unit: FEET},<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;details: CUMULONIMBUS<br>
&nbsp;&nbsp;&nbsp;&nbsp;cloudLayers[1]:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;amount: BROKEN<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;height: {height: 2800, unit: FEET},<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;details: NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS<br>
&nbsp;&nbsp;&nbsp;&nbsp;weather[0]:<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;phenomena: SHOWERY_PRECIPITATION_LIGHT<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;precipitation[0]: RAIN<br>
<br>
forecast:<br>
&nbsp;&nbsp;noSignificantChanges: true
</td>
</table>