// Basic gps

#include <HardwareSerial.h>
HardwareSerial gpsSerial(2); //16,17

// GPS read function
void gps_read()
{
  if (gpsSerial.available()) {
    char c = gpsSerial.read();  // Read one character
    if (c == '\n') {          // End of sentence
      if (nmeaSentence.startsWith("$GPGGA")) {
        extractLatLong(nmeaSentence); // Extract data if GPGGA sentence
      }
      nmeaSentence = ""; // Clear buffer for next sentence
    } else {
      nmeaSentence += c; // Append character to buffer
    }
  }
}

//gps function calculation
void extractLatLong(String nmea) {
  // Example GPGGA sentence: $GPGGA,123456.78,3723.2475,N,12202.3578,W,1,08,0.9,545.4,M,46.9,M,,*47
  String rawLat = getField(nmea, 2);  // Latitude value (raw)
  String latDir = getField(nmea, 3); // Latitude direction (N/S)
  String rawLon = getField(nmea, 4); // Longitude value (raw)
  String lonDir = getField(nmea, 5); // Longitude direction (E/W)

  Serial.print("Raw Lat: "); Serial.println(rawLat);
  Serial.print("Raw Lon: "); Serial.println(rawLon);

  // Convert raw latitude and longitude to decimal degrees
  latitude = convertToDecimal(rawLat);
  if (latDir == "S") latitude = -latitude; // South is negative

  longitude = convertToDecimal(rawLon);
  if (lonDir == "W") longitude = -longitude; // West is negative

  // Display latitude and longitude in decimal degrees
  Serial.print("Latitude: ");
  Serial.println(latitude, 6); // Print with 6 decimal places
  Serial.print("Longitude: ");
  Serial.println(longitude, 6); // Print with 6 decimal places
}

float convertToDecimal(String rawValue) {
  // Convert DDMM.MMMM to decimal degrees
  float value = rawValue.toFloat();
  int degrees = (int)(value / 100); // Extract degrees (integer part)
  float minutes = value - (degrees * 100); // Extract minutes
  return degrees + (minutes / 60); // Combine degrees and minutes
}

String getField(String data, int index) {
  // Extract specific field from NMEA sentence by commas
  int commaCount = 0;
  int startIndex = 0;
  for (size_t i = 0; i < data.length(); i++) {
    if (data[i] == ',') {
      commaCount++;
      if (commaCount == index) {
        startIndex = i + 1;
      } else if (commaCount == index + 1) {
        return data.substring(startIndex, i);
      }
    }
  }
  return ""; // Return empty string if field not found
}

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop()
{
  gps_read();
}

