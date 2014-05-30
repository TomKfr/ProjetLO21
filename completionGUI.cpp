#include "completionGUI.h"
#include "UTProfiler.h"
#include "completion.h"

MenuSouhaits::MenuSouhaits(souhaits *sht)
{
    this->setWindowTitle("Gérer les souhaits");
    objet=sht;

    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    hbox4=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    vbox3=new QVBoxLayout(this);
    vbox4=new QVBoxLayout(this);
    titre=new QLabel("Gérer les souhaits du dossier de ",this);
    lblneutre=new QLabel("UVs non associées à une liste",this);
    txtexigees=new QLabel("UVs exigees :",this);
    txtpreferees=new QLabel("UVS souhaitées :",this);
    txtrejetees=new QLabel("UVs rejetees :",this);
    listexigees=new QLabel("",this);
    listpreferees=new QLabel("",this);
    listrejetees=new QLabel("",this);
    exigeebutton=new QRadioButton("J'exige de faire cette UV",this);
    prefereebutton=new QRadioButton("J'aimerais faire cette UV",this);
    rejeteebutton=new QRadioButton("Je ne veux pas faire cette UV",this);
    valider1=new QPushButton("Ajouter",this);
    supprexigee=new QPushButton("Supprimer des exigences",this);
    supprpreferee=new QPushButton("Supprimer des préférences",this);
    supprrejetee=new QPushButton("Supprimer des rejets",this);
    sauver=new QPushButton("Sauvegarder",this);
    terminer=new QPushButton("Terminé",this);
    choix1=new QComboBox(this);
    choix2=new QComboBox(this);
    choix3=new QComboBox(this);
    choix4=new QComboBox(this);

    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    hbox2->addLayout(vbox1);
    hbox2->addLayout(hbox4);
    hbox4->addLayout(vbox2);
    hbox4->addLayout(vbox3);
    hbox4->addLayout(vbox4);

    hbox1->addWidget(titre);
    vbox1->addWidget(lblneutre);
    vbox1->addWidget(choix1);
    vbox1->addWidget(exigeebutton);
    vbox1->addWidget(prefereebutton);
    vbox1->addWidget(rejeteebutton);
    vbox1->addWidget(valider1);

    vbox2->addWidget(txtexigees);
    vbox2->addWidget(listexigees);
    vbox2->addWidget(choix2);
    vbox2->addWidget(supprexigee);

    vbox3->addWidget(txtpreferees);
    vbox3->addWidget(listpreferees);
    vbox3->addWidget(choix3);
    vbox3->addWidget(supprpreferee);

    vbox4->addWidget(txtrejetees);
    vbox4->addWidget(listrejetees);
    vbox4->addWidget(choix4);
    vbox4->addWidget(supprrejetee);

    hbox3->addWidget(sauver);
    hbox3->addWidget(terminer);

    this->setLayout(mainbox);

    /*QObject::connect(valider1,SIGNAL(clicked()),this,SLOT(ajUV()));
    QObject::connect(supprexigee,SIGNAL(clicked()),this,SLOT(suprexigee()));
    QObject::connect(supprpreferee,SIGNAL(clicked()),this,SLOT(suprpref()));
    QObject::connect(supprrejetee,SIGNAL(clicked()),this,SLOT(suprrejet()));
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(save()));*/
    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(close()));

    update();
}

void MenuSouhaits::update()
{
    UVManager& uman=UVManager::getInstance();
    QString list1;
    QString list2;
    QString list3;
    for(iterateur<UV>& it=uman.getIterateurForm();!it.isDone();it.next())
    {
        if(objet->estExigee(it.courant()->getCode()))
        {
            list1+=it.courant()->getCode()+"\n";
            choix2->addItem(it.courant()->getCode());
        }
        else
        {
            if(objet->estPreferee(it.courant()->getCode()))
            {
                list2+=it.courant()->getCode()+"\n";
                choix3->addItem(it.courant()->getCode());
            }
            else
            {
                if(objet->estRejetee(it.courant()->getCode()))
                {
                    list3+=it.courant()->getCode()+"\n";
                    choix4->addItem(it.courant()->getCode());
                }
                else
                {
                    choix1->addItem(it.courant()->getCode());
                }
            }
        }

        listexigees->setText(list1);
        listpreferees->setText(list2);
        listrejetees->setText(list3);
    }
}
