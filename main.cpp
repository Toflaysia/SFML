#include <SFML/Graphics.hpp>
const int window_width = 1200;
const int window_height = 720;
const int tile_width = 35;
const int tile_height = 48;

const int height = 10;
const int width = 105;

char tilemap[height][width] = {
"                                                                                                      ",
"               ttt    tt                                          ttt    tt                           ",
"                                                                                                      ",
"tt  ttttttt  tttt  ttttttt  tttt  ttttttttttt  tttttt  ttttttt  tttt  ttttttt  tttt  ttttttttttt  tttt",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
"oootttoooooooooooooooooooooooottoooooottooooottoottoootttoooooooooooooooooooooooottoooooottooooottoott",
"tooooooottooooooooootttooooooooooottoooooottoooootttooooooottooooooooootttooooooooooottoooooottooooott",
"tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt",
"tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt",
"tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt",
};
int main() {
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Game"); 
	sf::Image im; 
	im.loadFromFile("D:\\Study\\chip\\chip_anime.png");
	im.createMaskFromColor(sf::Color::White);
	sf::Texture t;
	t.loadFromImage(im);
	sf::Sprite s;  
	s.setTexture(t); 
	s.setTextureRect(sf::IntRect(0, 0, tile_width, tile_height));
	s.setPosition(0, 0);

	sf::Texture t2;
	t2.loadFromFile("D:\\Study\\chip\\tileset.png");
	sf::Sprite play_map;
	play_map.setTexture(t2); 

	float frame_num = 0;
	float dx = 0, dy = 0;
	bool ground = false;
	float jump = 0;
	sf::Clock clock;
	float x_pos = s.getPosition().x;
	float y_pos = s.getPosition().y;

	while (window.isOpen()) { 
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart();  
		sf::Event event; 
		while (window.pollEvent(event)) { 
			if (event.type == sf::Event::Closed)  
				window.close();   
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {          //движение вправо
			//if (s.getPosition().x <= (window_width - tile_width)) {
			if (x_pos <= tile_width * (width-1))
			{
				if (jump == 0) {
					frame_num += 0.00001 * time;
					if (frame_num > 3) {
						frame_num = 1;
					}
					s.setTextureRect(sf::IntRect(35 * (int)frame_num, 0, tile_width, tile_height));
				}
				dx = 0.0002;
				x_pos = x_pos + dx * time;
				//s.move(dx * time, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {             //движение влево
			if (x_pos >= 0) {
				if (jump == 0) {
					frame_num += 0.00001 * time;
					if (frame_num > 3) {
						frame_num = 1;
					}
					s.setTextureRect(sf::IntRect(35 * (int)(frame_num + 1), 0, -tile_width, tile_height));
				}
				dx = -0.0002;
				x_pos = x_pos + dx * time;
				//s.move(dx * time, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (ground == true)
			{
				if (dx > 0){
					s.setTextureRect(sf::IntRect(tile_width * 4, 0, tile_width, tile_height));
				}
				else {
					s.setTextureRect(sf::IntRect(tile_width * 5, 0, -tile_width, tile_height));
				}
				dy = -0.0003;
				jump = jump + dy * time;
				y_pos = y_pos + dy * time;
				//s.move(0, dy * time);
				ground = false;
			}
		}
			if (ground == false) 
			{
				if (jump<0 && jump>(-tile_height * 2)) 
				{
					dy = -0.00035; 
					jump = jump + dy * time; 
					y_pos = y_pos + dy * time;
					//s.move(0, dy * time); 
				}
			else{
				if (dx > 0){
					s.setTextureRect(sf::IntRect(tile_width * 4, 0, tile_width, tile_height));
				}
				else{
					s.setTextureRect(sf::IntRect(tile_width * 5, 0, -tile_width, tile_height));
				}
				jump = 0; 
				dy = 0.00025; 
				y_pos = y_pos + dy * time; 
				//s.move(0, dy * time); 
			}
		}

		int i = y_pos / tile_height; 
		int j = x_pos / tile_width; 

		if (dx > 0 && tilemap[i][j + 1] == 't' && tilemap[i][j] != 't') {
			//s.setPosition(tile_width * j, s.getPosition().y);
			x_pos = j * tile_width;
		}
		if (dx < 0 && tilemap[i][j] == 't' && tilemap[i][j + 1] != 't') {
			//s.setPosition(tile_width * (j + 1), s.getPosition().y);
			x_pos = j * tile_width + tile_width;
		}
		if (dy > 0 && (tilemap[i + 1][j] == 't' || tilemap[i + 1][j + 1] == 't') && tilemap[i][j] != 't') {
			//s.setPosition(s.getPosition().x, tile_height * i);
			y_pos = i * tile_height;
			ground = true;
			dy = 0;
			jump = 0;
			if (dx > 0) {
				s.setTextureRect(sf::IntRect(tile_width * 0, 0, tile_width, tile_height));
			}
			else {
				s.setTextureRect(sf::IntRect(tile_width * 1, 0, -tile_width, tile_height)); 
			}
		}
		if (dx > 0 && ground == true && tilemap[i + 1][j] != 't' && (j + 1) < width) {
			ground = false;
		}
		if (dx < 0 && ground == true && tilemap[i + 1][j + 1] != 't') {
			ground = false;
		}
		window.clear(sf::Color::White);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (tilemap[i][j] == ' ') {
					play_map.setTextureRect(sf::IntRect(tile_width * 0, 0, tile_width, tile_height));
				}
				if (tilemap[i][j] == 't') {
					play_map.setTextureRect(sf::IntRect(tile_width * 2, 0, tile_width, tile_height));
				}
				if (tilemap[i][j] == 'o') {
					play_map.setTextureRect(sf::IntRect(tile_width * 1, 0, tile_width, tile_height));
				}
				play_map.setPosition((j+3) * 35 - x_pos, (i+3) * 48 - y_pos);
				s.setPosition(tile_width * 3, tile_height * 3);

				window.draw(play_map);
			}
		}
		window.draw(s);
		window.display();  
	}


	return 0;
};
