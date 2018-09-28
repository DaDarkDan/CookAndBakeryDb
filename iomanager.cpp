#include "iomanager.h"
#include "QFile"
#include "QDir"
#include "recipe.h"
#include "ingredient.h"
#include "QXmlStreamWriter"
#include "QXmlStreamReader"
#include <string>
#include "QDirIterator"
#include <iostream>

IOManager::IOManager(){
    QDir* dir = new QDir();
    directoryPath = dir->currentPath();

    loadRecipes();
    loadIngredients();
}

IOManager::~IOManager(){}

void IOManager::loadRecipes(){
    QDirIterator it("/etc", QDirIterator::NoIteratorFlags);
    //start file parsing
    while(it.hasNext()){
        it.next();
        QFile file(it.next());
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            std::cerr << "Error: Cannot read file " << qPrintable(it.next())
                      << ": " << qPrintable(file.errorString()) << std::endl;
        }
        xmlReader->setDevice(&file);
        xmlReader->readNext();
        //start reading xml document
        while(!xmlReader->atEnd()){
            if(xmlReader->isStartElement()){
                if
            }
        }
    }
}

void IOManager::saveRecipe(Recipe recipe){
    //setup
    QString fileName = recipe.getName() + ".xml";

    QFile file(directoryPath + fileName);
    file.open(QIODevice::WriteOnly);

    xmlWriter = new QXmlStreamWriter(&file);

    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();

    //write to xml
    xmlWriter->writeStartElement("Recipe");

    xmlWriter->writeTextElement("name", recipe.getName());
    xmlWriter->writeTextElement("date", recipe.getCreationDateAsQString());
    xmlWriter->writeTextElement("category", recipe.getCategory());
    xmlWriter->writeTextElement("favourite", recipe.getFavouriteAsQString());
    xmlWriter->writeTextElement("notes", recipe.getNotes());

    //save ingredient list
    xmlWriter->writeStartElement("Ingredient");
    for (auto ingredient : recipe.getIngredients()){
        xmlWriter->writeTextElement("ingredientName", ingredient.getName());
        QString amount = QString::fromStdString(std::to_string(ingredient.getAmount()));
        xmlWriter->writeTextElement("ingredientAmount", amount);
        QString weightType = ingredient.getWeightTypes().at(ingredient.getWeightType());
        xmlWriter->writeTextElement("ingredientWeightType", weightType);
    }
    xmlWriter->writeEndElement();

    //save keyword list
    xmlWriter->writeStartElement("Keyword");
    for (auto keyword : recipe.getKeywords()){
        xmlWriter->writeTextElement("ingredientName", keyword);
    }
    xmlWriter->writeEndElement();

    file.close();
}

void IOManager::loadIngredients(){

}

void IOManager::saveIngredient(Ingredient ingredient){

}
