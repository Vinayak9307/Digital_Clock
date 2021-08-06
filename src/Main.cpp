#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

int SCREEN_W;
int SCREEN_H;

sf::Vector2f point;

sf::RenderWindow     app;
sf::RectangleShape  *rectangle;
sf::CircleShape     *circle;
sf::Text            *text;

void draw( );
void drawSegment( sf::Vector2f point , int a );
void drawRectangle( sf::Vector2f position , sf::Vector2f dimension , bool fill );
void drawRoundedRect( sf::Vector2f position , sf::Vector2f dimension , bool fill ,bool horizontal );
void drawCircle( float radius , sf::Vector2f position );

int num[10] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
tm * Time;

int main()
{
    srand(time(NULL));
    app.create(sf::VideoMode::getFullscreenModes()[0],"Led Clock",sf::Style::Fullscreen);
    app.setFramerateLimit(2);
    SCREEN_W = app.getSize( ).x;
    SCREEN_H = app.getSize( ).y;

    rectangle = new sf::RectangleShape( );
    circle    = new sf::CircleShape( ); 

    sf::Font font;
    font.loadFromFile( "D:/Project1/Led_Clock/resources/FlappyFont.ttf");

    text      = new sf::Text( );
    text->setFont( font );
    text->setCharacterSize( 40 );
    text->setFillColor( sf::Color::Red);
    

    point.x = SCREEN_W * 0.2;
    point.y = SCREEN_H * 0.35;

    text->setPosition(sf::Vector2f( point.x + 740, point.y + 125));
    
    time_t curent_time;

    while(app.isOpen()){

        sf::Event event;

        curent_time = time(NULL);
        Time = localtime( &curent_time );

        // std::cout<<Time->tm_hour<<" "<<Time->tm_min<<" "<<Time->tm_sec<<"\n";

        while(app.pollEvent(event)){

            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    app.close( );
                    break;
                
                default:
                    break;
                }
                break;
            case sf::Event::Closed:
                app.close( );
                break;
            
            default:
                break;
            }

        }
        app.clear( );
        draw( );
        app.display( );
    }
}
void draw( ){
    int hrs = Time->tm_hour%12;
    if(!hrs){
        hrs = 12;
    }
    int min = Time->tm_min;
    int sec = Time->tm_sec;

    //hours
    drawSegment( sf::Vector2f(point.x  , point.y), num[hrs/10]);
    drawSegment( sf::Vector2f(point.x + 110,point.y), num[hrs%10]);

    //minute
    drawSegment( sf::Vector2f(point.x + 260 , point.y), num[min/10]);
    drawSegment( sf::Vector2f(point.x + 370,point.y), num[min%10]);

    //seconds
    drawSegment( sf::Vector2f(point.x + 520,point.y ), num[sec/10]);
    drawSegment( sf::Vector2f(point.x + 630,point.y), num[sec%10]);

    //seperatingCircles
    drawCircle( 8,sf::Vector2f(point.x +220 , point.y + 40) );
    drawCircle( 8,sf::Vector2f(point.x +220 , point.y + 120) );
    drawCircle( 8,sf::Vector2f(point.x +480 , point.y + 40) );
    drawCircle( 8,sf::Vector2f(point.x +480 , point.y + 120) );

    /*   AM / PM mark */
    if(Time->tm_hour > 11){
        text->setString("PM");
    }
    else{
        text->setString("AM");
    }
    app.draw(*text);
    
}
bool light( int a , int value){
    bool temp = ((a >> value) & 1);
    return temp;
}
void drawSegment( sf::Vector2f point , int a){

drawRoundedRect( sf::Vector2f((point.x + 15) , point.y) , sf::Vector2f(50,10) , light(a,6) , 1);//A
drawRoundedRect( sf::Vector2f((point.x + 75) , (point.y + 15)) , sf::Vector2f(10,60) , light(a,5) , 0);//B
drawRoundedRect( sf::Vector2f((point.x + 75) , (point.y + 95)) , sf::Vector2f(10,60) , light(a,4) , 0);//C
drawRoundedRect( sf::Vector2f((point.x + 15) , (point.y + 160)) , sf::Vector2f(50,10) , light(a,3) , 1);//D
drawRoundedRect( sf::Vector2f((point.x - 5) , (point.y + 95)) , sf::Vector2f(10,60) , light(a,2) , 0);//E
drawRoundedRect( sf::Vector2f((point.x - 5) , (point.y + 15)) , sf::Vector2f(10,60) , light(a,1) , 0);//F
drawRoundedRect( sf::Vector2f((point.x + 15) , (point.y + 80)) , sf::Vector2f(50,10) , light(a,0) , 1);//G

}
void drawRectangle( sf::Vector2f position , sf::Vector2f dimension , bool fill){
    rectangle->setPosition( position );
    rectangle->setSize( dimension );
    if( fill ){
        rectangle->setFillColor(sf::Color(255,0,0,255));
    }else{
        rectangle->setFillColor(sf::Color(255,0,0,10));
    }
    app.draw( *rectangle );
}
void drawRoundedRect( sf::Vector2f position , sf::Vector2f dimension , bool fill , bool horizontal ){
    float radius;
    if(fill){
        circle->setFillColor( sf::Color(255,0,0,255));
    }
    else{
        circle->setFillColor( sf::Color(255,0,0,10));
    }
    if( horizontal ){
        radius = dimension.y/2;
        circle->setRadius( radius );
        circle->setPosition( sf::Vector2f( (position.x - radius) , position.y));
        app.draw( *circle );
        circle->setPosition( sf::Vector2f( (position.x + dimension.x - radius) , position.y));
        app.draw( *circle );
    }
    else{
        radius = dimension.x/2;
        circle->setRadius( radius );
        circle->setPosition( sf::Vector2f( (position.x) , (position.y - radius)));
        app.draw( *circle );
        circle->setPosition( sf::Vector2f( (position.x ) , (position.y+ dimension.y - radius)));
        app.draw( *circle );
    }

    drawRectangle( position , dimension , fill );
}
void drawCircle( float radius , sf::Vector2f position){
    circle->setRadius( radius );
    circle->setFillColor( sf::Color::Red );
    circle->setPosition( position );
    app.draw( *circle );
}