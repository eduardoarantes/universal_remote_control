
enum remote_control_codes
{
  /* names for main remote control buttons */
  left,
  right,
  up,
  down,
  enter,
  home,
  volume_up,
  volume_dow,
  red,
  blue,
  green,
  yellow
};

enum device_mode{
  CONFIGURING,
  RELAYING 
};

device_mode active_device_mode = RELAYING;

//Device list
const int FOXTEL_DEVICE = 1;
const int GOOGLE_DEVICE = 2;
const int SAMSUNG_DEVICE = 3;
const int SONY_DEVICE = 4;

int activeDevice = FOXTEL_DEVICE;
