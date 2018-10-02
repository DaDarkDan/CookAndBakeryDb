#include "iomanager.h"
#include "recipe.h"
#include "ingredient.h"

#include "QFile"
#include "QXmlStreamWriter"
#include "QXmlStreamReader"
#include "QDirIterator"
#include "QBuffer"
#include "QPixmap"
#include "QTextCodec"

#include <iostream>


IOManager::IOManager(){
    directoryPath = "D:/Daniel/Dokumente/QtProjects/recipefolder"; //TODO delete

    loadRecipes();
    loadIngredients();
}

IOManager::~IOManager(){}

vector<Recipe> IOManager::loadRecipes() const{
    Recipe* recipe = new Recipe();
    vector<Recipe> recipeList;

    QStringList filter("*.xml"); //only parse xml files
    QDirIterator it(directoryPath, filter);

    //start file parsing
    while(it.hasNext()){
        QFile file(it.next());
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            std::cerr << "Error: Cannot read file " << qPrintable(it.next())
                      << ": " << qPrintable(file.errorString()) << std::endl;
        }
        QXmlStreamReader xmlReader(&file);
        xmlReader.setDevice(&file);
        xmlReader.readNext();

        //start parsing xml file
        while(!xmlReader.isStartElement()){
            xmlReader.readNext();
        }
        if(xmlReader.name() == "Recipe"){
            xmlReader.readNext();
            xmlReader.readNext();
        } else {
            //TODO throw error
        }
        //name
        recipe->setName(xmlReader.readElementText());
        xmlReader.readNext();
        xmlReader.readNext();
        //date
        recipe->setCreationDate(xmlReader.readElementText());
        xmlReader.readNext();
        xmlReader.readNext();
        //category
        recipe->setCategory(xmlReader.readElementText());
        xmlReader.readNext();
        xmlReader.readNext();
        //favourite
        recipe->setFavourite(xmlReader.readElementText());
        xmlReader.readNext();
        xmlReader.readNext();
        //notes
        recipe->setNotes(xmlReader.readElementText());
        xmlReader.readNext();
        xmlReader.readNext();

        //ingredients
        xmlReader.readNext(); //StartElement
        xmlReader.readNext();
        Ingredient* ingredient = new Ingredient();
        while(xmlReader.name() == "IngredientName"){
            ingredient->setName(xmlReader.readElementText());
            xmlReader.readNext();
            xmlReader.readNext();
            ingredient->setAmount(std::stof(xmlReader.readElementText().toStdString()));
            xmlReader.readNext();
            xmlReader.readNext();
            ingredient->setWeightType(xmlReader.readElementText());
            xmlReader.readNext();
            xmlReader.readNext();
            recipe->addIngredient(*ingredient);
        }
        //keywords
        xmlReader.readNext(); //StartElement
        xmlReader.readNext();
        xmlReader.readNext();
        xmlReader.readNext();
        while (xmlReader.name() == "keyword"){
            recipe->addKeyword(xmlReader.readElementText());
            xmlReader.readNext();
            xmlReader.readNext();
        }
        recipe->setRating(xmlReader.readElementText().toInt());
        //picture
        QString imgFullPath = directoryPath + "/" + recipe->getName() +"_image.png";
        QPixmap* pixmap = new QPixmap();
        pixmap->load(imgFullPath);
        recipe->setPixmap(*pixmap);

        recipeList.push_back(*recipe);
    }
    return recipeList;
}

void IOManager::saveRecipe(Recipe recipe) const{
    //setup
    QString fileName = recipe.getName() + ".xml";

    QFile file(directoryPath + "/" + fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        //write to xml
        xmlWriter.writeStartElement("Recipe");

        xmlWriter.writeTextElement("Name", recipe.getName());
        xmlWriter.writeTextElement("Date", recipe.getCreationDate());
        xmlWriter.writeTextElement("Category", recipe.getCategory());
        xmlWriter.writeTextElement("Favourite", recipe.getFavouriteAsQString());
        xmlWriter.writeTextElement("Notes", recipe.getNotes());

        //save ingredient list
        xmlWriter.writeStartElement("Ingredient");
        for (auto ingredient : recipe.getIngredients()){
            xmlWriter.writeTextElement("IngredientName", ingredient.getName());
            QString amount = QString::fromStdString(std::to_string(ingredient.getAmount()));
            xmlWriter.writeTextElement("IngredientAmount", amount);
            QString weightType = ingredient.getWeightType();
            xmlWriter.writeTextElement("IngredientWeightType", weightType);
        }
        xmlWriter.writeEndElement();

        //save keyword list
        xmlWriter.writeStartElement("Keywords");
        for (auto keyword : recipe.getKeywords()){
            xmlWriter.writeTextElement("keyword", keyword);
        }
        xmlWriter.writeEndElement();

        //rating
        xmlWriter.writeTextElement("rating", QString::number(recipe.getRating()));

        //finish
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

    }
    file.close();
    //save image
    fileName = recipe.getName() + "_image.png";
    QFile imgFile(directoryPath + "/" + fileName);
    imgFile.open(QIODevice::WriteOnly);
    recipe.getPixmap().save(&imgFile, "PNG");
    imgFile.close();
}

vector<Ingredient> IOManager::loadIngredients() const {
    QStringList filter(ingFileName);
    QDirIterator it(directoryPath, filter);

    vector<Ingredient> ingredientList;

    if (it.hasNext()){
        QFile file(it.next());
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            std::cerr << "Error: Cannot read file " << qPrintable(it.next())
                      << ": " << qPrintable(file.errorString()) << std::endl;
        }
    }

    return ingredientList;
}

void IOManager::saveIngredients(vector<Ingredient> ingredients) const{
    QFile file(directoryPath + "/" + ingFileName);
    if (file.open(QIODevice::WriteOnly)){
        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        for (auto ing : ingredients){
            xmlWriter.writeStartElement("Ingredient");
            xmlWriter.writeTextElement("Name", ing.getName());
            xmlWriter.writeTextElement("Amount", QString::fromStdString(std::to_string(ing.getAmount())));
            xmlWriter.writeTextElement("WeightType", ing.getWeightType());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void IOManager::setDirectoryPath(const QString &value){
    directoryPath = value;
}

QString IOManager::getDirectoryPath() const{
    return directoryPath;
}
