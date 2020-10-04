#!/bin/bash
DEFAULT_SINK=$(pactl info | sed -En 's/Default Sink: (.*)/\1/p')
DEFAULT_SOURCE=$(pactl info | sed -En 's/Default Source: (.*)/\1/p')
pactl load-module module-null-sink sink_name=FAout sink_properties=device.description="FakeAudioOut"
pactl load-module module-null-sink sink_name=CAout sink_properties=device.description="CombinedAudioOut"
pactl load-module module-loopback sink=CAout source=FAout.monitor
pactl load-module module-loopback sink=CAout source=$DEFAULT_SOURCE
pactl load-module module-loopback sink=$DEFAULT_SINK source=FAout.monitor
