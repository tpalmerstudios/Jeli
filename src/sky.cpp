void drawGround (const GameState &gs, FrameBuffer &fb)
{
	Rectangle rect (0,
			gs.player.horizon,
			fb.getW (),
			fb.getH (),
			packColor (180, 180, 255));
	fb.drawOver (rect.getCoords (), rect.getColor ())
}
