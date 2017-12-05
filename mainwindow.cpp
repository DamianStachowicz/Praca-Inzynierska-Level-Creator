#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    itemID = 0;
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateView() {
    scene->clear();
    QGraphicsPixmapItem *item;
    Entity *entity;
    for(uint i = 0; i < Entity::entities.size(); ++i) {
        entity = Entity::entities[i];
        switch(entity->type) {
            case ENTITY_TYPE_PLANET: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Planet-Red.png")); break;
            case ENTITY_TYPE_ASTEROID:
                switch( ((Asteroid*)entity)->size ) {
                    case 1: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Asteroid-Small.png")); break;
                    case 2: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Asteroid-Middle.png")); break;
                    case 3: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Asteroid-Big.png")); break;
                }
                break;
            case ENTITY_TYPE_PARTICLE: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Particle.png")); break;
            case ENTITY_TYPE_ROCKET: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Rocket.png")); break;
            case ENTITY_TYPE_SELLING_POINT: item = new QGraphicsPixmapItem(QPixmap(":/gfx/sellingpoint.png")); break;
            case ENTITY_TYPE_SPACESHIP: item = new QGraphicsPixmapItem(QPixmap(":/gfx/Spaceship.png")); break;
        }
        item->setPos((qreal)(entity->location.x - entity->r), (qreal)(entity->location.y) - entity->r);
        item->setTransformOriginPoint(entity->r, entity->r);
        item->setRotation(entity->rotation);
        scene->addItem(item);
        QPen pen;
        QColor color(0, 0, 255);
        pen.setColor(color);
        pen.setWidth(3);
        scene->addLine(entity->location.x, entity->location.y,
                       entity->location.x + entity->velocity.x,
                       entity->location.y + entity->velocity.y,
                       pen);
        color = QColor(255, 255, 0);
        pen.setColor(color);
        pen.setWidth(1);
        scene->addEllipse(entity->location.x + entity->collisionCenter.x - entity->r,
                          entity->location.y + entity->collisionCenter.y - entity->r,
                          entity->r * 2, entity->r * 2, pen);
    }
    ui->graphicsView->show();
}

void MainWindow::on_xPosSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->xPosSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->location.x = value;
    UpdateView();
}

void MainWindow::on_yPosSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->yPosSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->location.y = value;
    UpdateView();
}

void MainWindow::on_xVelSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->xVelSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->velocity.x = value;
    UpdateView();
}

void MainWindow::on_yVelSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->yVelSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->velocity.y = value;
    UpdateView();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    int ID = arg1.split(" ")[0].toInt();
    if(entityList.count(ID) == 0)
        return;
    Entity *entity = entityList.at(ID);

    ui->xPosSpinBox->setValue(entity->location.x);
    ui->yPosSpinBox->setValue(entity->location.y);
    ui->xVelSpinBox->setValue(entity->velocity.x);
    ui->yVelSpinBox->setValue(entity->velocity.y);
    ui->massSpinBox->setValue(entity->mass);
    ui->colXPosSpinBox->setValue(entity->collisionCenter.x);
    ui->colYPosSpinBox->setValue(entity->collisionCenter.y);
    ui->colRPosSpinBox->setValue(entity->r);

    ui->graphicsView->centerOn(entity->location.x, entity->location.y);
}

void MainWindow::on_buttonAddPlanet_clicked()
{
    Planet *planet = new Planet();
    planet->Load(NULL, "gfx/Planet-Red.png", 218, 1, 1, vector2d(0, 0), 120000, vector2d(0, 2), 106);
    Entity::entities.push_back(planet);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Planeta");
    entityList.insert(std::pair<int, Entity*>(itemID, planet));
    ++itemID;

    ui->xPosSpinBox->setValue(planet->location.x);
    ui->yPosSpinBox->setValue(planet->location.y);
    ui->xVelSpinBox->setValue(planet->velocity.x);
    ui->yVelSpinBox->setValue(planet->velocity.y);
    ui->massSpinBox->setValue(planet->mass);
    ui->colXPosSpinBox->setValue(planet->collisionCenter.x);
    ui->colYPosSpinBox->setValue(planet->collisionCenter.y);
    ui->colRPosSpinBox->setValue(planet->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::on_asteroidBigAdd_clicked()
{
    AsteroidBig *asteroid = new AsteroidBig();
    asteroid->Load(NULL, "gfx/Asteroid-Big.png", 98, 1, 1, vector2d(0, 0), 12000);
    Entity::entities.push_back(asteroid);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Asteroida D");
    entityList.insert(std::pair<int, Entity*>(itemID, asteroid));
    ++itemID;

    ui->xPosSpinBox->setValue(asteroid->location.x);
    ui->yPosSpinBox->setValue(asteroid->location.y);
    ui->xVelSpinBox->setValue(asteroid->velocity.x);
    ui->yVelSpinBox->setValue(asteroid->velocity.y);
    ui->massSpinBox->setValue(asteroid->mass);
    ui->colXPosSpinBox->setValue(asteroid->collisionCenter.x);
    ui->colYPosSpinBox->setValue(asteroid->collisionCenter.y);
    ui->colRPosSpinBox->setValue(asteroid->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::on_asteroidMediumAdd_clicked()
{
    AsteroidMiddle *asteroid = new AsteroidMiddle();
    asteroid->Load(NULL, "gfx/Asteroid-Middle.png", 89, 1, 1, vector2d(0, 0), 6000);
    Entity::entities.push_back(asteroid);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Asteroida Ś");
    entityList.insert(std::pair<int, Entity*>(itemID, asteroid));
    ++itemID;

    ui->xPosSpinBox->setValue(asteroid->location.x);
    ui->yPosSpinBox->setValue(asteroid->location.y);
    ui->xVelSpinBox->setValue(asteroid->velocity.x);
    ui->yVelSpinBox->setValue(asteroid->velocity.y);
    ui->massSpinBox->setValue(asteroid->mass);
    ui->colXPosSpinBox->setValue(asteroid->collisionCenter.x);
    ui->colYPosSpinBox->setValue(asteroid->collisionCenter.y);
    ui->colRPosSpinBox->setValue(asteroid->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::on_asteroidSmallAdd_clicked()
{
    AsteroidSmall *asteroid = new AsteroidSmall();
    asteroid->Load(NULL, "gfx/Asteroid-Small.png", 43, 1, 1, vector2d(0, 0), 3000);
    Entity::entities.push_back(asteroid);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Asteroida M");
    entityList.insert(std::pair<int, Entity*>(itemID, asteroid));
    ++itemID;

    ui->xPosSpinBox->setValue(asteroid->location.x);
    ui->yPosSpinBox->setValue(asteroid->location.y);
    ui->xVelSpinBox->setValue(asteroid->velocity.x);
    ui->yVelSpinBox->setValue(asteroid->velocity.y);
    ui->massSpinBox->setValue(asteroid->mass);
    ui->colXPosSpinBox->setValue(asteroid->collisionCenter.x);
    ui->colYPosSpinBox->setValue(asteroid->collisionCenter.y);
    ui->colRPosSpinBox->setValue(asteroid->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::on_levelEdgeSpinBox_editingFinished()
{
    double value = ui->levelEdgeSpinBox->value();
    ui->xPosSpinBox->setMaximum(value);
    ui->xPosSpinBox->setMinimum(-value);
    ui->yPosSpinBox->setMaximum(value);
    ui->yPosSpinBox->setMinimum(-value);
}

void MainWindow::on_rotationSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->rotationSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->rotation = value;
    UpdateView();
}

void MainWindow::on_massSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->massSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->mass = value;
    UpdateView();
}

void MainWindow::on_sellingPointAdd_clicked()
{
    SellingPoint *sellingPoint = new SellingPoint(NULL);
    sellingPoint->Load(NULL, "gfx/sellingpoint.png", 200, 1, 1, vector2d(0, 0), 1);
    Entity::entities.push_back(sellingPoint);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Punkt sprzedaży");
    entityList.insert(std::pair<int, Entity*>(itemID, sellingPoint));
    ++itemID;

    ui->xPosSpinBox->setValue(sellingPoint->location.x);
    ui->yPosSpinBox->setValue(sellingPoint->location.y);
    ui->xVelSpinBox->setValue(sellingPoint->velocity.x);
    ui->yVelSpinBox->setValue(sellingPoint->velocity.y);
    ui->massSpinBox->setValue(sellingPoint->mass);
    ui->colXPosSpinBox->setValue(sellingPoint->collisionCenter.x);
    ui->colYPosSpinBox->setValue(sellingPoint->collisionCenter.y);
    ui->colRPosSpinBox->setValue(sellingPoint->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::UpdateComboBox() {
    ui->comboBox->clear();
    Entity *entity;
    for(uint i = 0; i < Entity::entities.size(); ++i) {
        entity = Entity::entities[i];
        QString type;
        switch(entity->type) {
            case ENTITY_TYPE_PLANET: type = "Planeta"; break;
            case ENTITY_TYPE_ASTEROID:
                switch( ((Asteroid*)entity)->size ) {
                    case 1: type = "Asteroida M"; break;
                    case 2: type = "Asteroida Ś"; break;
                    case 3: type = "Asteroida D"; break;
                }
                break;
            case ENTITY_TYPE_PARTICLE: type = "Cząstka"; break;
            case ENTITY_TYPE_ROCKET: type = "Rakieta"; break;
            case ENTITY_TYPE_SELLING_POINT: type = "Punkt sprzedaży"; break;
            case ENTITY_TYPE_SPACESHIP:
                type = "Statek kosmiczny";
                ui->playerComboBox->addItem(QString::number(itemID) + " Statek kosmiczny");
                break;
            default: type = "???";
        }

        ui->comboBox->addItem(QString::number(itemID) + " " + type);
        entityList.insert(std::pair<int, Entity*>(itemID, entity));
        ++itemID;
    }

}

void MainWindow::on_actionWczytaj_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Wczytaj poziom"), "./", tr("Pliki XML (*.xml)"));
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError result = xmlDoc.LoadFile(fileName.toUtf8().constData());
    tinyxml2::XMLNode* root = xmlDoc.FirstChild();

    if( result != tinyxml2::XML_SUCCESS ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Błąd", "Nie udało się otworzyć pliku " + fileName + " do odczytu");
        messageBox.setFixedSize(500,200);
        return;
    }

    tinyxml2::XMLElement* element = root->FirstChildElement("level");
    if( !Entity::level.Deserialize(element) ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Błąd", "Nie udało szczytać informacji o obszarze rozgrywki");
        messageBox.setFixedSize(500,200);
        return;
    }
    element = root->FirstChildElement("timer");
    if( !Entity::timer.Deserialize(element) ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Błąd", "Nie udało szczytać informacji o timerze");
        messageBox.setFixedSize(500,200);
        return;
    }
    element = root->FirstChildElement("entities");
    tinyxml2::XMLElement* listElement = element->FirstChildElement();
    Uint32 tmp;
    Entity* tmpEntity;
    while(listElement != NULL) {
        if( std::string(listElement->Name()) == "Asteroid" ) {
            listElement->FirstChildElement("size")->QueryUnsignedText(&tmp);
            Asteroid* asteroid;
            switch(tmp) {
                case ASTEROID_SIZE_BIG: {
                    asteroid = new AsteroidBig();
                    asteroid->Deserialize(listElement, NULL);
                    Entity::entities.push_back(asteroid);
                    break;
                }
                case ASTEROID_SIZE_MIDDLE: {
                    asteroid = new AsteroidMiddle();
                    asteroid->Deserialize(listElement, NULL);
                    Entity::entities.push_back(asteroid);
                    break;
                }
                case ASTEROID_SIZE_SMALL:  {
                    asteroid = new AsteroidSmall();
                    asteroid->Deserialize(listElement, NULL);
                    Entity::entities.push_back(asteroid);
                    break;
                }
                default:  {
                    asteroid = new Asteroid();
                    asteroid->Deserialize(listElement, NULL);
                    Entity::entities.push_back(asteroid);
                    break;
                }
            }
        } else if( std::string(listElement->Name()) == "SpaceShip" ) {
            SpaceShip* spaceShip = new SpaceShip();
            spaceShip->Deserialize(listElement, NULL);
            Entity::entities.push_back(spaceShip);
        } else if( std::string(listElement->Name()) == "Particle" ) {
            Particle* particle = new Particle();
            particle->Deserialize(listElement, NULL);
            Entity::entities.push_back(particle);
        } else if( std::string(listElement->Name()) == "Planet" ) {
            Planet* planet = new Planet();
            planet->Deserialize(listElement, NULL);
            Entity::entities.push_back(planet);
        } else if( std::string(listElement->Name()) == "Rocket" ) {
            Rocket* rocket = new Rocket();
            rocket->Deserialize(listElement, NULL);
            Entity::entities.push_back(rocket);
        } else if( std::string(listElement->Name()) == "SellingPoint" ) {
            SellingPoint* sellingPoint = new SellingPoint(NULL);
            sellingPoint->Deserialize(listElement, NULL);
            Entity::entities.push_back(sellingPoint);
        } else {
            tmpEntity = new Entity();
            tmpEntity->Deserialize(listElement, NULL);
            Entity::entities.push_back(tmpEntity);
        }
        listElement = listElement->NextSiblingElement();
    }

    UpdateView();
    UpdateComboBox();
}

void MainWindow::on_actionZapisz_triggered()
{
    tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
    tinyxml2::XMLNode* root = xmlDoc->NewElement("Engine");
    xmlDoc->InsertFirstChild(root);
    tinyxml2::XMLElement* element = xmlDoc->NewElement("score");
    element->SetText(0);
    root->InsertEndChild(element);
    element = xmlDoc->NewElement("entities");
    tinyxml2::XMLElement* subelement;
    std::string entityType;
    for(uint i = 0; i < Entity::entities.size(); i++) {
        switch(Entity::entities[i]->type) {
            case ENTITY_TYPE_ASTEROID: entityType = "Asteroid"; break;
            case ENTITY_TYPE_PARTICLE: entityType = "Particle"; break;
            case ENTITY_TYPE_PLANET: entityType = "Planet"; break;
            case ENTITY_TYPE_ROCKET: entityType = "Rocket"; break;
            case ENTITY_TYPE_SELLING_POINT: entityType = "SellingPoint"; break;
        case ENTITY_TYPE_SPACESHIP: entityType = "SpaceShip"; break;
            default: entityType = "Default";
        }
        subelement = xmlDoc->NewElement(entityType.c_str());
        if( !Entity::entities[i]->Serialize(xmlDoc, subelement) ) {
            return;
        }
        element->InsertEndChild(subelement);
    }
    root->InsertEndChild(element);
    element = xmlDoc->NewElement("level");
    if( !Entity::level.Serialize(xmlDoc, element) ) {
        return;
    }
    root->InsertEndChild(element);
    element = xmlDoc->NewElement("timer");
    if( !Entity::timer.Serialize(xmlDoc, element) ) {
        return;
    }
    root->InsertEndChild(element);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz poziom"), "./", tr("Pliki XML (*.xml)"));
    tinyxml2::XMLError result = xmlDoc->SaveFile(fileName.toUtf8().constData());
    if( result != tinyxml2::XML_SUCCESS ) {
        QMessageBox messageBox;
        messageBox.critical(0, "Błąd", "Nie udało się zapisać pliku " + fileName);
        messageBox.setFixedSize(500,200);
        return;
    }
}

void MainWindow::on_zoomButtonUp_clicked()
{
    ui->graphicsView->scale(2, 2);
}

void MainWindow::on_zoomButtonDown_clicked()
{
    ui->graphicsView->scale(0.5, 0.5);
}

void MainWindow::on_spaceshipAdd_clicked()
{
    SpaceShip *spaceShip = new SpaceShip();
    spaceShip->Load(NULL, "gfx/Spaceship.png", 102, 1, 1, vector2d(0, 0), 1000);
    Entity::entities.push_back(spaceShip);
    UpdateView();
    ui->comboBox->addItem(QString::number(itemID) + " Statek kosmiczny");
    ui->playerComboBox->addItem(QString::number(itemID) + " Statek kosmiczny");
    entityList.insert(std::pair<int, Entity*>(itemID, spaceShip));
    ++itemID;

    ui->xPosSpinBox->setValue(spaceShip->location.x);
    ui->yPosSpinBox->setValue(spaceShip->location.y);
    ui->xVelSpinBox->setValue(spaceShip->velocity.x);
    ui->yVelSpinBox->setValue(spaceShip->velocity.y);
    ui->massSpinBox->setValue(spaceShip->mass);
    ui->colXPosSpinBox->setValue(spaceShip->collisionCenter.x);
    ui->colYPosSpinBox->setValue(spaceShip->collisionCenter.y);
    ui->colRPosSpinBox->setValue(spaceShip->r);

    ui->comboBox->setCurrentIndex(ui->comboBox->count() -1);
}

void MainWindow::on_colXPosSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->colXPosSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->collisionCenter.x = value;
    UpdateView();
}

void MainWindow::on_colYPosSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->colYPosSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->collisionCenter.y = value;
    UpdateView();
}

void MainWindow::on_colRPosSpinBox_editingFinished()
{
    if(ui->comboBox->count() == 0)
        return;
    double value = ui->colRPosSpinBox->value();
    int ID = ui->comboBox->currentText().split(" ")[0].toInt();
    Entity *entity = entityList.at(ID);
    entity->r = value;
    UpdateView();
}
