bool outOfBounds(int x, int y){
	return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}
int arrIndex(int x, int y, int height) {
	return y * height + x;
}