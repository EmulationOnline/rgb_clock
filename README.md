# RGB Clock

This little demonstration renders a gradient
background, with a bar that smoothly moves from top to bottom and back.

The core logic writes to a RGBA framebuffer in memory,
and is drawn once per frame.

It is thus a helpful demo for testing out high performance rendering from a
framebuffer. The bar moves one pixel per frame, so with a framebuffer height of 240 pixels
should take about 4 seconds to reach the bottom.
