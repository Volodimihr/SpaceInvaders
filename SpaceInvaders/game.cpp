#include "game.h"

bool Game::getThe_end() const
{
    return the_end;
}

void Game::setThe_end(bool end)
{
    the_end = end;
}

int Game::getArmy_size() const
{
    return army_size;
}

void Game::setArmy_size(int as)
{
    army_size = as;
}

int Game::getLeft_flank() const
{
    return left_flank;
}

void Game::setLeft_flank(int lf)
{
    left_flank = lf;
}

int Game::getRight_flank() const
{
    return right_flank;
}

void Game::setRight_flank(int rf)
{
    right_flank = rf;
}

bool Game::e_r() const
{
    return m_e_r;
}

void Game::setE_r(bool mr)
{
    m_e_r = mr;
}

bool Game::e_l() const
{
    return m_e_l;
}

void Game::setE_l(bool ml)
{
    m_e_l = ml;
}

int Game::getEnemy_line() const
{
    return enemy_line;
}

void Game::setEnemy_line(int el)
{
    enemy_line = el;
}

bool Game::getWinner() const
{
    return winner;
}

void Game::setWinner(bool w)
{
    winner = w;
}

QPoint *Game::getBlast() const
{
    return blast;
}

void Game::setBlast(QPoint *bl)
{
    blast = bl;
}

Game::Game(QWidget *parent) : QWidget(parent) // создание главного виджета
{
    gen = new QRandomGenerator(QDateTime::currentSecsSinceEpoch()); // генератор случайных чисел

    QFontDatabase::addApplicationFont(":/INVASION2000.TTF"); // подключение шрифта

    resize(SC_WIDTH, SC_HEIGHT); // размер виджета
    QPalette pal;
    pal.setColor(QPalette::ColorRole(backgroundRole()), Qt::black);
    setAutoFillBackground(true);
    setPalette(pal); // визуальные параметры виджета

    for(int i = 0; i < 10; i++){
        enemy_list.push_back(Enemy(i*64+32, 80, ":/enemy8_32.png")); // создание юнитов инопланетян с координатами и изображением
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 10; j++){
            enemy_list.push_back(Enemy(j*64+31, i*64+144, ":/enemy10_32.png"));
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 10; j++){
            enemy_list.push_back(Enemy(j*64+30, i*64+272, ":/enemy12_32.png"));
        }
    }

    setArmy_size(enemy_list.size()); // запоминаем размер армии

    def = new Defender(SC_WIDTH/2-16, SC_HEIGHT-32, ":/defender.png"); // создание юнита защитника
    blast = new QPoint(0,0); // точка выстрела врага
    timerId = startTimer(50); // запускаю таймер игры

    timer = new QTimer(this); // запускаю новый  таймер для стрельбы врага
    timer->setInterval(3000);
    connect(timer, &QTimer::timeout, [this](){
        enemy_bullet.push_back(Bullet(blast->x(), blast->y(), ":/blast.png"));
    });
    timer->start();
}

Game::~Game()
{
    delete def;
    delete gen;
    delete timer;
    delete blast;
}

void Game::paintEvent(QPaintEvent *e) // создание события для рисования
{
    Q_UNUSED(e);
    QPainter p(this);

    if(getThe_end())
    {
        game_over(&p);
    }

    if(getWinner())
    {
        you_win(&p); //
    }

    // отрисовка врагов
    for(int i = 0; i < enemy_list.size(); i++){
        p.drawImage(enemy_list[i].getRect().topLeft(), enemy_list[i].getImage());
    }

    for(int i = 0; i < enemy_bullet.size(); i++){
        p.drawImage(enemy_bullet[i].getRect().topLeft(), enemy_bullet[i].getImage());
    }

    for(int i = 0; i < bullet_list.size(); i++){
        p.drawImage(bullet_list[i].getRect().topLeft(), bullet_list[i].getImage());
    }

    // отрисовка защитника
    p.drawImage(def->getRect().topLeft(), def->getImage());
}

void Game::timerEvent(QTimerEvent *e) // таймер обновления событий
{
    Q_UNUSED(e);

    intersecting();

    if(def->getDead()){
        setThe_end(true);
        timer->stop();
        killTimer(timerId);
    }

    for(int i = 0; i < bullet_list.size(); i++) { // удаление незадействованных пуль
        if(bullet_list[i].getDead())
            bullet_list.remove(i);
    }

    int lf = SC_WIDTH;
    int rf = 0;
    for(int i = 0; i < enemy_list.size(); i++) {
        {   // получение координат левого и правого фланга врага
            lf = (enemy_list[i].getRect().left()<lf?enemy_list[i].getRect().left():lf);
            setLeft_flank(lf);
            rf = (enemy_list[i].getRect().right()>rf?enemy_list[i].getRect().right():rf);
            setRight_flank(rf);
        }

        if(enemy_list[i].getDead()) // удаление уничтоженных врагов
            enemy_list.remove(i);
    }

    setArmy_size(enemy_list.size());
    if(getArmy_size()==0) // проверка, уничтожена ли вся армия врага
    {
        setWinner(true);
        timer->stop();
        killTimer(timerId);
    }

    if(getArmy_size()>0){   // пока в армии есть истребители
        int r = gen->bounded(0, getArmy_size()); // случайный истребитель стреляет
        blast->setX(enemy_list[r].getRect().x()+16);
        blast->setY(enemy_list[r].getRect().bottom());
    }

    enemyMoving();

    // направление и скорость полета пуль защитника и врага
    for_each(bullet_list.begin(), bullet_list.end(), [](Bullet &b)->void{b.translate(0, -16);});
    for_each(enemy_bullet.begin(), enemy_bullet.end(), [](Bullet &b)->void{b.translate(0, 16);});

    // передовая линия врага
    setEnemy_line(enemy_list.isEmpty()?LAST_LINE:enemy_list.last().getRect().bottom());

    update();
}

void Game::keyReleaseEvent(QKeyEvent *e) // события при отпускании кнопок
{
    int x = 0;
    switch(e->key()) {
    case Qt::Key_Left:
        def->translate(x, 0);
        break;
    case Qt::Key_Right:
        def->translate(x, 0);
        break;
    }
}

void Game::intersecting() // пересечение площадей объектов
{
    if(getEnemy_line()>LAST_LINE) // пересечение площадей передовой линии врага и передовой линии защитника
        setThe_end(true);

    for_each(enemy_bullet.begin(), enemy_bullet.end(), [this](Bullet &b){
        if(b.getRect().intersects(def->getRect())) // пересечение площадей пули врага и защитника
            def->setDead(true);
        if(!rect().contains(b.getRect()))
            b.setDead(true);
    });

    // проверка, вылетела ли пуля за пределы виджета
    for_each(bullet_list.begin(), bullet_list.end(), [this](Bullet &b)->void{
        if(!rect().contains(b.getRect()))
            b.setDead(true);
        // пересечение площадей пули защитника и и истребителями врага
        for_each(enemy_list.begin(), enemy_list.end(), [&b](Enemy &e)->void{
            if(b.getRect().intersects(e.getRect())){
                e.setDead(true);
                b.setDead(true);
            }
        });
    });
}

void Game::keyPressEvent(QKeyEvent *e) // событие при нажатии кнопок
{
    int x = 0;
    switch(e->key()) {
    case Qt::Key_Space:
        shoot();
        break;
    case Qt::Key_Escape:
        qApp->quit();
        break;
    case Qt::Key_Left:
        // смещение на определенное количество клеток(пикселей)
        if(def->getRect().left()>8)
            x = -12;
        else
            x = 0;
        def->translate(x, 0);
        break;
    case Qt::Key_Right:
        if(def->getRect().right()<SC_WIDTH-8)
            x = 12;
        else
            x = 0;
        def->translate(x, 0);
        break;
    default:
        break;
    }
}

void Game::enemyMoving() // наступательное движение врага
{
    int mx = 0;
    int my = 0;
    int ms = (55-army_size)/5;
    if(!getThe_end())
    {
        if(e_r() && getRight_flank()<SC_WIDTH-16){
            mx = ms;
        }
        else if(e_l() && getLeft_flank()>16){
            mx = -(ms);
        }
        else {
            my = 16;
            setE_r(!e_r());
            setE_l(!e_l());
        }
    }
    else{
        timer->stop();
    }

    for_each(enemy_list.begin(), enemy_list.end(), [mx, my](Enemy &e){e.translate(mx, my);});

}

void Game::shoot() // выстрелы защитника
{
    bullet_list.push_back(Bullet(def->getRect().left()+14, def->getRect().top(), ":/bullet.png"));
}

void Game::game_over(QPainter *p) // объявление о проигрыше
{
    QStringList fonts = {"Invasion2000", "Lucida Console", "Arial", "Times New Roman"};
    QFont font(fonts, 96, QFont::Bold);
    QFontMetrics fm(font);
    p->setFont(font);
    p->setPen(Qt::white);
    p->translate(QPoint(width()/2, height()/2));
    p->drawText(-fm.horizontalAdvance("Game Over!")/2, 0, "Game Over!");
}

void Game::you_win(QPainter *p) // объявление о победе
{
    QStringList fonts = {"Invasion2000", "Lucida Console", "Arial", "Times New Roman"};
    QFont font(fonts, 96, QFont::Bold);
    QFontMetrics fm(font);
    p->setFont(font);
    p->setPen(Qt::white);
    p->translate(QPoint(width()/2, height()/2));
    p->drawText(-fm.horizontalAdvance("You Win!")/2, 0, "You Win!");
}
