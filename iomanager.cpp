#include "iomanager.h"
#include "recipe.h"
#include "ingredient.h"
#include "pathpixmap.h"

#include "QFile"
#include "QXmlStreamWriter"
#include "QDirIterator"
#include "QBuffer"
#include "QPixmap"
#include "QTextCodec"
#include "QMap"

#include <iostream>

IOManager::~IOManager(){}

QList<Recipe*> IOManager::loadRecipes() {
    QStringList filter = {"*xml", "*png"};

    //read files
    QDir dir(directoryPath);
    dir.setNameFilters(filter);
    dir.setSorting(QDir::SortFlag::Name);
    QFileInfoList fileList = dir.entryInfoList();

    QList<Recipe*> recipeList;
    QList<PathPixmap*> pixmapList;
    while(!fileList.empty()){
        QFile file(fileList.at(0).absoluteFilePath());
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            std::cerr << "Error: Cannot read file " << file.fileName().toStdString();
            continue;
        }
        if (fileList.at(0).absoluteFilePath().endsWith(".xml")){
            QXmlStreamReader* xmlReader = new QXmlStreamReader(fileList.at(0).absoluteFilePath());
            xmlReader->setDevice(&file);
            recipeList.push_back(parseRecipe(xmlReader));
        } else if (fileList.at(0).absoluteFilePath().endsWith(".png")){
            PathPixmap* ppm = parsePixmap(fileList.at(0).absoluteFilePath());
            //since it's sorted add pixmaps to last corresponding last recipe
            recipeList.last()->addPixmap(*ppm);
        }
        fileList.removeAt(0);
    }
    return recipeList;
}

Recipe *IOManager::parseRecipe(QXmlStreamReader* xmlReader){
    xmlReader->readNext();

    while(!xmlReader->isStartElement()){
        xmlReader->readNext();
    }
    if(xmlReader->name() == "Recipe"){
        xmlReader->readNext();
        xmlReader->readNext();
    }
    Recipe* recipe = new Recipe();
    //id
    recipe->setId(xmlReader->readElementText());
    recipe->setFullPath(directoryPath + "/" + recipe->getId() + ".xml");
    xmlReader->readNext();
    xmlReader->readNext();
    //name
    recipe->setName(xmlReader->readElementText());
    xmlReader->readNext();
    xmlReader->readNext();
    //date
    recipe->setCreationDate(xmlReader->readElementText());
    xmlReader->readNext();
    xmlReader->readNext();
    //category
    recipe->setCategory(xmlReader->readElementText());
    xmlReader->readNext();
    xmlReader->readNext();
    //favourite
    recipe->setFavourite(xmlReader->readElementText());
    xmlReader->readNext();
    xmlReader->readNext();
    //notes
    recipe->setNotes(xmlReader->readElementText());
    xmlReader->readNext();
    xmlReader->readNext();

    //ingredients
    xmlReader->readNext(); //StartElement
    xmlReader->readNext();
    Ingredient* ingredient = new Ingredient();
    while(xmlReader->name() == "IngredientName"){
        ingredient->setName(xmlReader->readElementText());
        xmlReader->readNext();
        xmlReader->readNext();
        ingredient->setAmount(std::stof(xmlReader->readElementText().toStdString()));
        xmlReader->readNext();
        xmlReader->readNext();
        ingredient->setWeightType(xmlReader->readElementText());
        xmlReader->readNext();
        xmlReader->readNext();
        recipe->addIngredient(*ingredient);
    }
    //keywords
    xmlReader->readNext(); //StartElement
    xmlReader->readNext();
    xmlReader->readNext();
    xmlReader->readNext();
    while (xmlReader->name() == "keyword"){
        recipe->addKeyword(xmlReader->readElementText());
        xmlReader->readNext();
        xmlReader->readNext();
    }
    //rating
    xmlReader->readNext();
    xmlReader->readNext();
    recipe->setRating(xmlReader->readElementText().toInt());

    return recipe;
}

PathPixmap *IOManager::parsePixmap(QString path){
    QPixmap* pixmap = new QPixmap();
    pixmap->load(path);
    return new PathPixmap(path, *pixmap);
}

void IOManager::saveRecipe(Recipe* recipe) const{
    //setup
    QString fileName = recipe->getId() + ".xml";
    recipe->setFullPath(directoryPath + "/" + fileName);

    QFile file(directoryPath + "/" + fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        //write to xml
        xmlWriter.writeStartElement("Recipe");

        xmlWriter.writeTextElement("id", recipe->getId());
        xmlWriter.writeTextElement("Name", recipe->getName());
        xmlWriter.writeTextElement("Date", recipe->getCreationDate());
        xmlWriter.writeTextElement("Category", recipe->getCategory());
        xmlWriter.writeTextElement("Favourite", recipe->getFavouriteAsQString());
        xmlWriter.writeTextElement("Notes", recipe->getNotes());

        //save ingredient list
        xmlWriter.writeStartElement("Ingredient");
        for (auto ingredient : recipe->getIngredients()){
            xmlWriter.writeTextElement("IngredientName", ingredient.getName());
            QString amount = QString::fromStdString(std::to_string(ingredient.getAmount()));
            xmlWriter.writeTextElement("IngredientAmount", amount);
            QString weightType = ingredient.getWeightType();
            xmlWriter.writeTextElement("IngredientWeightType", weightType);
        }
        xmlWriter.writeEndElement();

        //save keyword list
        xmlWriter.writeStartElement("Keywords");
        for (auto keyword : recipe->getKeywords()){
            xmlWriter.writeTextElement("keyword", keyword);
        }
        xmlWriter.writeEndElement();

        //rating
        xmlWriter.writeTextElement("rating", QString::number(recipe->getRating()));

        //finish
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

    }
    file.close();
    //save images
    if (!recipe->getPixmapList().empty()){
        for (int i = 0; i < recipe->getPixmapList().size(); i++){
            fileName = recipe->getPixmapList().at(i).getPath();
            QFile imgFile(fileName);
            imgFile.open(QIODevice::WriteOnly);
            recipe->getPixmapList().at(i).getPixmap().save(&imgFile, "PNG");
            imgFile.close();
        }
    }
}

void IOManager::setDirectoryPath(const QString &value){
    directoryPath = value;
}

QString IOManager::getDirectoryPath() const{
    return directoryPath;
}
