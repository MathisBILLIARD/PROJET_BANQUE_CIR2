#include "MyFrame.hpp"
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <random>
#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
namespace pt = boost::property_tree;
constexpr int MIN = 1;
constexpr int MAX = 100;
constexpr int RAND_NUMS_TO_GENERATE = 10;

wxIMPLEMENT_APP(App);

//--------------------------------------------------------------------------//
//                                   SETUP                                  //
//--------------------------------------------------------------------------//

//---------------- FRAME ----------------//
bool App::OnInit() {
	Connexion* setup = new Connexion("Soci�t� G�n�rale | Accueil");
	setup->SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	setup->SetClientSize(1000, 600);
	setup->Center();
	setup->Show();
	return true;
}

//---------------- IDENTIFIANT DES INTERACTIONS ----------------//
enum IDs {
	//Panel Connexion & Inscription
	PRENOM = 1,
	NOM = 2,
	ADRESSE = 3,
	CODECLIENT = 4,
	CHECKBOX = 5,
	OUVRIRCOMPTE = 6,
	VALIDERCONNEXION = 7,
	//Panel Compte Bancaire
	USERINFORMATION = 8,
	LIEUHEURE = 9,
	COMPTEBANCAIRE = 10,
	COMPTE1 = 11,
	COMPTE2 = 12,
	MONTANTBANCAIRE = 13,
	MONTANT1 = 14,
	MONTANT2 = 15,
	NUMEROCOMPTEBANCAIRE = 16,
	NUMEROCOMPTE1 = 17,
	NUMEROCOMPTE2 = 18,
	VALIDERCREATION = 19,
	VIREMENT = 20,
	DECONNEXION = 21,
	SUPPRESSIONCOMPTE = 22,
	SUPPRESSIONCOMPTE1 = 23,
	NOMCOMPTECREATION = 24,
	MONTANTCOMPTECREATION = 25,
	//Panel Virement & Depot
	VALIDERVIREMENT = 26,
	VALIDERDEPOT = 27,
	COMPTE = 28,
	BENEFICIAIRE = 29,
	MONTANTVIREMENT = 30,
	POURQUOI = 31,
	MONTANTDEPOT = 32,
	CHOIX = 33
};



//--------------------------------------------------------------------------//
//                         CONNEXION & INSCRIPTION                          //
//--------------------------------------------------------------------------//

//---------------- EVENEMENTS & METHODES ----------------//

wxBEGIN_EVENT_TABLE(Connexion, wxFrame)
EVT_BUTTON(VALIDERCONNEXION, Connexion::BtnValider)
EVT_UPDATE_UI(VALIDERCONNEXION, Connexion::VerificationConnexion)
EVT_UPDATE_UI(OUVRIRCOMPTE, Connexion::VerificationInscription)
EVT_BUTTON(OUVRIRCOMPTE, Connexion::BtnOuvrirUnCompte)
wxEND_EVENT_TABLE()

//V�rification donn�e cr�ation de compte (Register)
void Connexion::VerificationInscription(wxUpdateUIEvent& event) {
	if (InputPrenom->GetValue().IsEmpty() || InputNom->GetValue().IsEmpty() || InputAdresse->GetValue().IsEmpty() || !checkBox->IsChecked() == 1) {
		event.Enable(false);
		return;
	}
	event.Enable(true);
}



//V�rification donn�e connexion au compte (Login)
void Connexion::VerificationConnexion(wxUpdateUIEvent& event) {
	if (!InputCodeClient->GetValue().IsNumber() || InputCodeClient->GetValue().IsEmpty()) {
		event.Enable(false);
		return;
	}
	event.Enable(true);
}

//Fonction ouvrir un compte (button register)
void Connexion::BtnOuvrirUnCompte(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(InputPrenom->GetValue(), InputNom->GetValue(), InputAdresse->GetValue(), InputCodeClient->GetValue(), this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	if (dlg->ShowModal() == OUVRIRCOMPTE) { //Si le code Client est correct -> Ouvrir l'espace personnel
	}
}

//Fonction ouvrir la connexion (button login)
void Connexion::BtnValider(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(InputCodeClient->GetValue(), this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	if (dlg->ShowModal() == VALIDERCREATION) { //Si le code Client est correct -> Ouvrir l'espace personnel
	}
}

//---------------- DESIGN DU PANEL  ----------------//

Connexion::Connexion(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	//D�finition du Panel Connexion
	wxPanel* PanelConnexion = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelConnexion->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher les images
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Header = new wxStaticBitmap(PanelConnexion, wxID_ANY, wxBitmap("head.bmp", wxBITMAP_TYPE_BMP)); //Image Header
	wxStaticBitmap* CarteBleu = new wxStaticBitmap(PanelConnexion, wxID_ANY, wxBitmap("cb.bmp", wxBITMAP_TYPE_BMP), wxPoint(590, 320)); //Image CB

	//Texte 
	wxStaticText* TextPrenom = new wxStaticText(PanelConnexion, wxID_ANY, "Pr�nom", wxPoint(40, 180)); //Pr�nom
	wxStaticText* TextNom = new wxStaticText(PanelConnexion, wxID_ANY, "Nom", wxPoint(40, 270)); //Nom
	wxStaticText* TextAdresse = new wxStaticText(PanelConnexion, wxID_ANY, "Adresse", wxPoint(40, 360)); //Adresse
	wxStaticText* TextCodeClient = new wxStaticText(PanelConnexion, wxID_ANY, "Code du Client", wxPoint(590, 180)); //Num�ro de Client

	//Input
	InputPrenom = new wxTextCtrl(PanelConnexion, PRENOM, "", wxPoint(40, 200), wxSize(280, 35)); //Prenom
	InputPrenom->SetFont(InputPrenom->GetFont().Scale(1.3));
	InputNom = new wxTextCtrl(PanelConnexion, NOM, "", wxPoint(40, 290), wxSize(280, 35)); //Nom
	InputNom->SetFont(InputNom->GetFont().Scale(1.3));
	InputAdresse = new wxTextCtrl(PanelConnexion, ADRESSE, "", wxPoint(40, 380), wxSize(280, 35)); //Adresse
	InputAdresse->SetFont(InputAdresse->GetFont().Scale(1.3));
	InputCodeClient = new wxTextCtrl(PanelConnexion, CODECLIENT, "", wxPoint(590, 200), wxSize(280, 35), wxTE_PASSWORD); //Code Client + MDP cach�
	InputCodeClient->SetFont(InputCodeClient->GetFont().Scale(1.3));

	//Checkbox
	checkBox = new wxCheckBox(PanelConnexion, CHECKBOX, "Je d�clare �tre majeur et � utiliser ce compte � titre individuel", wxPoint(40, 435));

	//Bouton Ouvrir un compte
	wxButton* BtnOuvrirCompte = new wxButton(PanelConnexion, OUVRIRCOMPTE, "OUVRIR UN COMPTE", wxPoint(40, 480), wxSize(200, 40), wxBORDER_NONE);
	BtnOuvrirCompte->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnOuvrirCompte->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnOuvrirCompte->SetFont(BtnOuvrirCompte->GetFont().MakeBold()); //Mettre en gras

	//Bouton Valider
	wxButton* BtnValider = new wxButton(PanelConnexion, VALIDERCONNEXION, "VALIDER", wxPoint(590, 260), wxSize(200, 40), wxBORDER_NONE);
	BtnValider->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValider->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValider->SetFont(BtnValider->GetFont().MakeBold());

	//Barre de S�paration
	wxStaticText* Barre = new wxStaticText(PanelConnexion, wxID_ANY, "", wxPoint(500, 200), wxSize(2, 300));
	Barre->SetBackgroundColour(*wxLIGHT_GREY); //Gris
}



//--------------------------------------------------------------------------//
//                       COMPTE BANCAIRE INDIVIDUEL                         //
//--------------------------------------------------------------------------//

//---------------- EVENEMENTS & METHODES ----------------//

wxBEGIN_EVENT_TABLE(CompteBancaire, wxDialog)
EVT_BUTTON(VIREMENT, CompteBancaire::BtnVirement)
EVT_BUTTON(VALIDERCREATION, CompteBancaire::BtnValiderCreation)
EVT_BUTTON(SUPPRESSIONCOMPTE, CompteBancaire::BtnSuppressioncompte)
EVT_BUTTON(SUPPRESSIONCOMPTE1, CompteBancaire::BtnSuppressioncompte1)
EVT_BUTTON(DECONNEXION, CompteBancaire::BtnDeconnexion)
EVT_UPDATE_UI(VALIDERCREATION, CompteBancaire::VerificationCreation)
wxEND_EVENT_TABLE()

//Fonction Ouvrir un nouveau panel
void CompteBancaire::BtnVirement(wxCommandEvent& evt) {
	Virement* dlg = new Virement(client, codeclient, this, wxID_ANY, ("Soci�t� G�n�rale | Virement & D�p�t"));
	Close(); //Fermer le panel Espace Personnel
	if (dlg->ShowModal() == VIREMENT) {  // Ouvrir le panel Virement & D�p�t
	}
}

//Fonction Bouton Valider Cr�ation de compte
void CompteBancaire::BtnValiderCreation(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(client, codeclient, InputCompteCreation->GetValue(), InputMontantCreation->GetValue(), this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	Close();
	if (dlg->ShowModal() == VALIDERCREATION) {
		
	}
}

//Fonction Bouton Suppression compte 
void CompteBancaire::BtnSuppressioncompte(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(client, codeclient, 1, this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	Close();
	if (dlg->ShowModal() == SUPPRESSIONCOMPTE) {
	}
}

//Fonction Bouton Suppression compte 1
void CompteBancaire::BtnSuppressioncompte1(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(client, codeclient, 2, this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	Close();
	if (dlg->ShowModal() == SUPPRESSIONCOMPTE1) {
	}
}

//Fonction Bouton Deconnexion de la session
void CompteBancaire::BtnDeconnexion(wxCommandEvent& evt) {
	Destroy();
}

//V�rification donn�e cr�ation de compte autres
void CompteBancaire::VerificationCreation(wxUpdateUIEvent& event) {
	if (!InputMontantCreation->GetValue().IsNumber() || InputCompteCreation->GetValue().IsEmpty() || InputMontantCreation->GetValue().empty()) {
		event.Enable(false);
		return;
	}
	event.Enable(true);
}

//---------------- DESIGN DU PANEL  ----------------//

CompteBancaire::CompteBancaire(wxString prenom, wxString nom, wxString adresse, wxString codeclient, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->prenom = prenom;
	this->nom = nom;
	this->adresse = adresse;

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();
	//D�finition du Panel Compte Bancaire
	wxPanel* PanelCompteBancaire = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelCompteBancaire, wxID_ANY, wxBitmap("Compte.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	//Texte Bande Noir : pr�nom Nom | Num�ro
	// Create a root
	pt::ptree root;
	vector<Customer> client;
	// Load the json file in this ptree
	std::ifstream file_in("filename.json");
	pt::read_json(file_in, root);
	for (ptree::value_type& customer : root.get_child("Customers"))
	{
		int number = customer.second.get<int>("Number", 0);
		std::string name = customer.second.get<std::string>("Name");
		std::string address = customer.second.get<std::string>("Adress");
		std::vector<Compte> account_numbers;
		for (ptree::value_type& account_number : customer.second.get_child("Account_numbers")) {
			Compte comptes(account_number.second.get<string>("Name"), account_number.second.get<int>("Numero"), account_number.second.get<int>("Money"));
			account_numbers.push_back(comptes);
		}
		Customer custom(number, std::move(name), std::move(account_numbers), std::move(address));
		client.push_back(custom);
	}
	constexpr int MIN = 1;
	constexpr int MAX = 100;
	constexpr int RAND_NUMS_TO_GENERATE = 10;
	string appel;
	appel = prenom + nom;
	Compte compte;
	vector<Compte> comptes;
	comptes.push_back(compte);
	int number = client.size()+2314;
	Customer c(number, std::move(appel), std::move(comptes), std::move(static_cast<string>(adresse)));
	client.push_back(c);
	int num;
	num = c.comptes_[0].numero_compte;

	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (c.comptes_.size() >= 2) {
		nomCompte1 = c.comptes_[1].name;
		montant1 = to_string(c.comptes_[1].money)+" �";
		numero1 = to_string(abs(c.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (c.comptes_.size() >= 3) {
		nomCompte2 = c.comptes_[2].name;
		montant2 = to_string(c.comptes_[2].money)+" �";
		numero2 = to_string(abs(c.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->codeclient = to_string(c.number_);
	this->client = client;
	wxStaticText* TextUser = new wxStaticText(PanelCompteBancaire, USERINFORMATION, wxString::Format("%s %s | %d %s", prenom, nom, c.number_, adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &CompteBancaire::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelCompteBancaire, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Texte Compte Bancaire
	wxStaticText* TextCompteBancaire = new wxStaticText(PanelCompteBancaire, COMPTEBANCAIRE, c.comptes_[0].name, wxPoint(50, 145));
	wxFont fontCompte1 = TextCompteBancaire->GetFont();
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().MakeBold());
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().Scale(1.1));
	//Texte Compte Cr�e 1
	wxStaticText* TextCompte1 = new wxStaticText(PanelCompteBancaire, COMPTE1, nomCompte1, wxPoint(50, 278));
	TextCompte1->SetFont(TextCompte1->GetFont().MakeBold());
	TextCompte1->SetFont(TextCompte1->GetFont().Scale(1.1));
	//Texte Compte Cr�e 2
	wxStaticText* TextCompte2 = new wxStaticText(PanelCompteBancaire, COMPTE2, nomCompte2, wxPoint(50, 353));
	TextCompte2->SetFont(TextCompte2->GetFont().MakeBold());
	TextCompte2->SetFont(TextCompte2->GetFont().Scale(1.1));

	//Texte Montant Compte Bancaire
	wxStaticText* TextMontantBancaire = new wxStaticText(PanelCompteBancaire, MONTANTBANCAIRE, to_string(c.comptes_[0].money) + " �", wxPoint(530, 145));
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().MakeBold());
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().Scale(1.1));
	//Texte Montant 1
	wxStaticText* TextMontant1 = new wxStaticText(PanelCompteBancaire, MONTANT1, montant1, wxPoint(530, 278));
	TextMontant1->SetFont(TextMontant1->GetFont().MakeBold());
	TextMontant1->SetFont(TextMontant1->GetFont().Scale(1.1));
	//Texte Montant 2
	wxStaticText* TextMontant2 = new wxStaticText(PanelCompteBancaire, MONTANT2, montant2, wxPoint(530, 353));
	TextMontant2->SetFont(TextMontant2->GetFont().MakeBold());
	TextMontant2->SetFont(TextMontant2->GetFont().Scale(1.1));

	//Texte Num�ro Compte Bancaire
	wxStaticText* TextNum�roCompteBancaire = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTEBANCAIRE, to_string(abs(num)), wxPoint(50, 178));
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().MakeBold());
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().Scale(1.1));
	TextNum�roCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompteBancaire->SetForegroundColour(wxColour(111, 111, 111)); //gris
	//Texte Num�ro Compte 1
	wxStaticText* TextNum�roCompte1 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE1, numero1, wxPoint(50, 311));
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().MakeBold());
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().Scale(1.1));
	TextNum�roCompte1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte1->SetForegroundColour(wxColour(224, 52, 0)); //rouge
	//Texte Num�ro Compte 2
	wxStaticText* TextNum�roCompte2 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE2, numero2, wxPoint(50, 386));
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().MakeBold());
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().Scale(1.1));
	TextNum�roCompte2->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte2->SetForegroundColour(wxColour(224, 52, 0)); //rouge

	//Bouton Valider
	wxButton* BtnValiderCreation = new wxButton(Fond, VALIDERCREATION, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderCreation->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderCreation->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderCreation->SetFont(BtnValiderCreation->GetFont().MakeBold());

	//Bouton Virement
	wxButton* BtnVirement = new wxButton(Fond, VIREMENT, "VIREMENT", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnVirement->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	BtnVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnVirement->SetFont(BtnVirement->GetFont().MakeBold());

	//Bouton Deconnexion
	wxButton* BtnDeconnexionCompte = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionCompte->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionCompte->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionCompte->SetFont(BtnDeconnexionCompte->GetFont().MakeBold());

	//Bouton Suppression Compte 
	BtnSuppression = new wxButton(Fond, SUPPRESSIONCOMPTE, "Suppression de compte", wxPoint(453, 307), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression->SetFont(BtnSuppression->GetFont().MakeBold());
	//Bouton Suppression Compte 1
	BtnSuppression1 = new wxButton(Fond, SUPPRESSIONCOMPTE1, "Suppression de compte", wxPoint(453, 382), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression1->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression1->SetFont(BtnSuppression1->GetFont().MakeBold());
	

	//Input compte
	InputCompteCreation = new wxTextCtrl(Fond, NOMCOMPTECREATION, "", wxPoint(690, 135), wxSize(250, 35));
	InputCompteCreation->SetFont(InputCompteCreation->GetFont().Scale(1.3));

	//Input Montant
	InputMontantCreation = new wxTextCtrl(Fond, MONTANTCOMPTECREATION, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantCreation->SetFont(InputMontantCreation->GetFont().Scale(1.3));
}

CompteBancaire::CompteBancaire(wxString codeclient, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();
	//D�finition du Panel Compte Bancaire
	wxPanel* PanelCompteBancaire = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelCompteBancaire, wxID_ANY, wxBitmap("Compte.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	//Texte Bande Noir : pr�nom Nom | Num�ro
	// Create a root
	pt::ptree root;
	vector<Customer> client;
	// Load the json file in this ptree
	std::ifstream file_in("filename.json");
	pt::read_json(file_in, root);
	for (ptree::value_type& customer : root.get_child("Customers"))
	{
		int number = customer.second.get<int>("Number");
		std::string name = customer.second.get<std::string>("Name");
		std::string address = customer.second.get<std::string>("Adress");
		std::vector<Compte> account_numbers;
		for (ptree::value_type& account_number : customer.second.get_child("Account_numbers")) {
			Compte comptes(account_number.second.get<string>("Name"), account_number.second.get<int>("Numero"), account_number.second.get<int>("Money"));
			account_numbers.push_back(comptes);
		}
		Customer custom(number, std::move(name), std::move(account_numbers), std::move(address));
		client.push_back(custom);
	}
	
	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	Customer cust = client[r];
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money)+" �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money)+" �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->client = client;
	this->prenom = cust.name_;
	this->adresse = cust.adresse;
	wxStaticText* TextUser = new wxStaticText(PanelCompteBancaire, USERINFORMATION, wxString::Format("%s | %d %s", cust.name_, code, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &CompteBancaire::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelCompteBancaire, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Texte Compte Bancaire
	wxStaticText* TextCompteBancaire = new wxStaticText(PanelCompteBancaire, COMPTEBANCAIRE, cust.comptes_[0].name, wxPoint(50, 145));
	wxFont fontCompte1 = TextCompteBancaire->GetFont();
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().MakeBold());
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().Scale(1.1));
	//Texte Compte Cr�e 1
	wxStaticText* TextCompte1 = new wxStaticText(PanelCompteBancaire, COMPTE1, nomCompte1, wxPoint(50, 278));
	TextCompte1->SetFont(TextCompte1->GetFont().MakeBold());
	TextCompte1->SetFont(TextCompte1->GetFont().Scale(1.1));
	//Texte Compte Cr�e 2
	wxStaticText* TextCompte2 = new wxStaticText(PanelCompteBancaire, COMPTE2, nomCompte2, wxPoint(50, 353));
	TextCompte2->SetFont(TextCompte2->GetFont().MakeBold());
	TextCompte2->SetFont(TextCompte2->GetFont().Scale(1.1));

	//Texte Montant Compte Bancaire
	wxStaticText* TextMontantBancaire = new wxStaticText(PanelCompteBancaire, MONTANTBANCAIRE, to_string(cust.comptes_[0].money)+" �", wxPoint(530, 145));
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().MakeBold());
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().Scale(1.1));
	//Texte Montant 1
	wxStaticText* TextMontant1 = new wxStaticText(PanelCompteBancaire, MONTANT1,montant1, wxPoint(530, 278));
	TextMontant1->SetFont(TextMontant1->GetFont().MakeBold());
	TextMontant1->SetFont(TextMontant1->GetFont().Scale(1.1));
	//Texte Montant 2
	wxStaticText* TextMontant2 = new wxStaticText(PanelCompteBancaire, MONTANT2, montant2, wxPoint(530, 353));
	TextMontant2->SetFont(TextMontant2->GetFont().MakeBold());
	TextMontant2->SetFont(TextMontant2->GetFont().Scale(1.1));

	//Texte Num�ro Compte Bancaire
	wxStaticText* TextNum�roCompteBancaire = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTEBANCAIRE, to_string(abs(num)), wxPoint(50, 178));
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().MakeBold());
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().Scale(1.1));
	TextNum�roCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompteBancaire->SetForegroundColour(wxColour(111, 111, 111)); //gris
	//Texte Num�ro Compte 1
	wxStaticText* TextNum�roCompte1 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE1, numero1, wxPoint(50, 311));
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().MakeBold());
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().Scale(1.1));
	TextNum�roCompte1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte1->SetForegroundColour(wxColour(224, 52, 0)); //rouge
	//Texte Num�ro Compte 2
	wxStaticText* TextNum�roCompte2 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE2, numero2, wxPoint(50, 386));
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().MakeBold());
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().Scale(1.1));
	TextNum�roCompte2->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte2->SetForegroundColour(wxColour(224, 52, 0)); //rouge

	//Bouton Valider
	wxButton* BtnValiderCreation = new wxButton(Fond, VALIDERCREATION, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderCreation->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderCreation->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderCreation->SetFont(BtnValiderCreation->GetFont().MakeBold());

	//Bouton Virement
	wxButton* BtnVirement = new wxButton(Fond, VIREMENT, "VIREMENT", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnVirement->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	BtnVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnVirement->SetFont(BtnVirement->GetFont().MakeBold());

	//Bouton Deconnexion
	wxButton* BtnDeconnexionCompte = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionCompte->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionCompte->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionCompte->SetFont(BtnDeconnexionCompte->GetFont().MakeBold());

	//Bouton Suppression Compte 
	BtnSuppression = new wxButton(Fond, SUPPRESSIONCOMPTE, "Suppression de compte", wxPoint(453, 307), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression->SetFont(BtnSuppression->GetFont().MakeBold());
	//Bouton Suppression Compte 1
	BtnSuppression1 = new wxButton(Fond, SUPPRESSIONCOMPTE1, "Suppression de compte", wxPoint(453, 382), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression1->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression1->SetFont(BtnSuppression1->GetFont().MakeBold());

	//Input compte
	InputCompteCreation = new wxTextCtrl(Fond, NOMCOMPTECREATION, "", wxPoint(690, 135), wxSize(250, 35));
	InputCompteCreation->SetFont(InputCompteCreation->GetFont().Scale(1.3));

	//Input Montant
	InputMontantCreation = new wxTextCtrl(Fond, MONTANTCOMPTECREATION, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantCreation->SetFont(InputMontantCreation->GetFont().Scale(1.3));
}

CompteBancaire::CompteBancaire(vector<Customer> client, wxString codeclient, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;
	this->client = client;

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();
	//D�finition du Panel Compte Bancaire
	wxPanel* PanelCompteBancaire = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelCompteBancaire, wxID_ANY, wxBitmap("Compte.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	//Texte Bande Noir : pr�nom Nom | Num�ro
	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	Customer cust = client[r];
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money)+" �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money)+" �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;
	wxStaticText* TextUser = new wxStaticText(PanelCompteBancaire, USERINFORMATION, wxString::Format("%s | %d %s", cust.name_, code, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &CompteBancaire::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelCompteBancaire, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Texte Compte Bancaire
	wxStaticText* TextCompteBancaire = new wxStaticText(PanelCompteBancaire, COMPTEBANCAIRE, cust.comptes_[0].name, wxPoint(50, 145));
	wxFont fontCompte1 = TextCompteBancaire->GetFont();
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().MakeBold());
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().Scale(1.1));
	//Texte Compte Cr�e 1
	wxStaticText* TextCompte1 = new wxStaticText(PanelCompteBancaire, COMPTE1, nomCompte1, wxPoint(50, 278));
	TextCompte1->SetFont(TextCompte1->GetFont().MakeBold());
	TextCompte1->SetFont(TextCompte1->GetFont().Scale(1.1));
	//Texte Compte Cr�e 2
	wxStaticText* TextCompte2 = new wxStaticText(PanelCompteBancaire, COMPTE2, nomCompte2, wxPoint(50, 353));
	TextCompte2->SetFont(TextCompte2->GetFont().MakeBold());
	TextCompte2->SetFont(TextCompte2->GetFont().Scale(1.1));

	//Texte Montant Compte Bancaire
	wxStaticText* TextMontantBancaire = new wxStaticText(PanelCompteBancaire, MONTANTBANCAIRE, to_string(cust.comptes_[0].money) + " �", wxPoint(530, 145));
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().MakeBold());
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().Scale(1.1));
	//Texte Montant 1
	wxStaticText* TextMontant1 = new wxStaticText(PanelCompteBancaire, MONTANT1, montant1, wxPoint(530, 278));
	TextMontant1->SetFont(TextMontant1->GetFont().MakeBold());
	TextMontant1->SetFont(TextMontant1->GetFont().Scale(1.1));
	//Texte Montant 2
	wxStaticText* TextMontant2 = new wxStaticText(PanelCompteBancaire, MONTANT2, montant2, wxPoint(530, 353));
	TextMontant2->SetFont(TextMontant2->GetFont().MakeBold());
	TextMontant2->SetFont(TextMontant2->GetFont().Scale(1.1));

	//Texte Num�ro Compte Bancaire
	wxStaticText* TextNum�roCompteBancaire = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTEBANCAIRE, to_string(abs(num)), wxPoint(50, 178));
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().MakeBold());
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().Scale(1.1));
	TextNum�roCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompteBancaire->SetForegroundColour(wxColour(111, 111, 111)); //gris
	//Texte Num�ro Compte 1
	wxStaticText* TextNum�roCompte1 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE1, numero1, wxPoint(50, 311));
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().MakeBold());
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().Scale(1.1));
	TextNum�roCompte1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte1->SetForegroundColour(wxColour(224, 52, 0)); //rouge
	//Texte Num�ro Compte 2
	wxStaticText* TextNum�roCompte2 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE2, numero2, wxPoint(50, 386));
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().MakeBold());
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().Scale(1.1));
	TextNum�roCompte2->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte2->SetForegroundColour(wxColour(224, 52, 0)); //rouge

	//Bouton Valider
	wxButton* BtnValiderCreation = new wxButton(Fond, VALIDERCREATION, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderCreation->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderCreation->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderCreation->SetFont(BtnValiderCreation->GetFont().MakeBold());

	//Bouton Virement
	wxButton* BtnVirement = new wxButton(Fond, VIREMENT, "VIREMENT", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnVirement->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	BtnVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnVirement->SetFont(BtnVirement->GetFont().MakeBold());

	//Bouton Deconnexion
	wxButton* BtnDeconnexionCompte = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionCompte->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionCompte->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionCompte->SetFont(BtnDeconnexionCompte->GetFont().MakeBold());

	//Bouton Suppression Compte 
	BtnSuppression = new wxButton(Fond, SUPPRESSIONCOMPTE, "Suppression de compte", wxPoint(453, 307), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression->SetFont(BtnSuppression->GetFont().MakeBold());
	//Bouton Suppression Compte 1
	BtnSuppression1 = new wxButton(Fond, SUPPRESSIONCOMPTE1, "Suppression de compte", wxPoint(453, 382), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression1->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression1->SetFont(BtnSuppression1->GetFont().MakeBold());

	//Input compte
	InputCompteCreation = new wxTextCtrl(Fond, NOMCOMPTECREATION, "", wxPoint(690, 135), wxSize(250, 35));
	InputCompteCreation->SetFont(InputCompteCreation->GetFont().Scale(1.3));

	//Input Montant
	InputMontantCreation = new wxTextCtrl(Fond, MONTANTCOMPTECREATION, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantCreation->SetFont(InputMontantCreation->GetFont().Scale(1.3));
}

CompteBancaire::CompteBancaire(vector<Customer> client, wxString codeclient,int numCompte, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();
	//D�finition du Panel Compte Bancaire
	wxPanel* PanelCompteBancaire = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelCompteBancaire, wxID_ANY, wxBitmap("Compte.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	//Texte Bande Noir : pr�nom Nom | Num�ro
	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	client[r].comptes_.erase(client[r].comptes_.begin()+numCompte);
	Customer cust = client[r];
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money) + " �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money) + " �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;
	this->client = client;
	wxStaticText* TextUser = new wxStaticText(PanelCompteBancaire, USERINFORMATION, wxString::Format("%s | %d %s", cust.name_, code, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &CompteBancaire::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelCompteBancaire, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Texte Compte Bancaire
	wxStaticText* TextCompteBancaire = new wxStaticText(PanelCompteBancaire, COMPTEBANCAIRE, cust.comptes_[0].name, wxPoint(50, 145));
	wxFont fontCompte1 = TextCompteBancaire->GetFont();
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().MakeBold());
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().Scale(1.1));
	//Texte Compte Cr�e 1
	wxStaticText* TextCompte1 = new wxStaticText(PanelCompteBancaire, COMPTE1, nomCompte1, wxPoint(50, 278));
	TextCompte1->SetFont(TextCompte1->GetFont().MakeBold());
	TextCompte1->SetFont(TextCompte1->GetFont().Scale(1.1));
	//Texte Compte Cr�e 2
	wxStaticText* TextCompte2 = new wxStaticText(PanelCompteBancaire, COMPTE2, nomCompte2, wxPoint(50, 353));
	TextCompte2->SetFont(TextCompte2->GetFont().MakeBold());
	TextCompte2->SetFont(TextCompte2->GetFont().Scale(1.1));

	//Texte Montant Compte Bancaire
	wxStaticText* TextMontantBancaire = new wxStaticText(PanelCompteBancaire, MONTANTBANCAIRE, to_string(cust.comptes_[0].money) + " �", wxPoint(530, 145));
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().MakeBold());
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().Scale(1.1));
	//Texte Montant 1
	wxStaticText* TextMontant1 = new wxStaticText(PanelCompteBancaire, MONTANT1, montant1, wxPoint(530, 278));
	TextMontant1->SetFont(TextMontant1->GetFont().MakeBold());
	TextMontant1->SetFont(TextMontant1->GetFont().Scale(1.1));
	//Texte Montant 2
	wxStaticText* TextMontant2 = new wxStaticText(PanelCompteBancaire, MONTANT2, montant2, wxPoint(530, 353));
	TextMontant2->SetFont(TextMontant2->GetFont().MakeBold());
	TextMontant2->SetFont(TextMontant2->GetFont().Scale(1.1));

	//Texte Num�ro Compte Bancaire
	wxStaticText* TextNum�roCompteBancaire = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTEBANCAIRE, to_string(abs(num)), wxPoint(50, 178));
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().MakeBold());
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().Scale(1.1));
	TextNum�roCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompteBancaire->SetForegroundColour(wxColour(111, 111, 111)); //gris
	//Texte Num�ro Compte 1
	wxStaticText* TextNum�roCompte1 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE1, numero1, wxPoint(50, 311));
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().MakeBold());
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().Scale(1.1));
	TextNum�roCompte1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte1->SetForegroundColour(wxColour(224, 52, 0)); //rouge
	//Texte Num�ro Compte 2
	wxStaticText* TextNum�roCompte2 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE2, numero2, wxPoint(50, 386));
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().MakeBold());
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().Scale(1.1));
	TextNum�roCompte2->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte2->SetForegroundColour(wxColour(224, 52, 0)); //rouge

	//Bouton Valider
	wxButton* BtnValiderCreation = new wxButton(Fond, VALIDERCREATION, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderCreation->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderCreation->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderCreation->SetFont(BtnValiderCreation->GetFont().MakeBold());

	//Bouton Virement
	wxButton* BtnVirement = new wxButton(Fond, VIREMENT, "VIREMENT", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnVirement->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	BtnVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnVirement->SetFont(BtnVirement->GetFont().MakeBold());

	//Bouton Deconnexion
	wxButton* BtnDeconnexionCompte = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionCompte->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionCompte->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionCompte->SetFont(BtnDeconnexionCompte->GetFont().MakeBold());

	//Bouton Suppression Compte 
	BtnSuppression = new wxButton(Fond, SUPPRESSIONCOMPTE, "Suppression de compte", wxPoint(453, 307), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression->SetFont(BtnSuppression->GetFont().MakeBold());
	//Bouton Suppression Compte 1
	BtnSuppression1 = new wxButton(Fond, SUPPRESSIONCOMPTE1, "Suppression de compte", wxPoint(453, 382), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression1->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression1->SetFont(BtnSuppression1->GetFont().MakeBold());
	//Input compte
	InputCompteCreation = new wxTextCtrl(Fond, NOMCOMPTECREATION, "", wxPoint(690, 135), wxSize(250, 35));
	InputCompteCreation->SetFont(InputCompteCreation->GetFont().Scale(1.3));

	//Input Montant
	InputMontantCreation = new wxTextCtrl(Fond, MONTANTCOMPTECREATION, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantCreation->SetFont(InputMontantCreation->GetFont().Scale(1.3));
}

CompteBancaire::CompteBancaire(vector<Customer> client, wxString codeclient, wxString CompteNom, wxString Montant, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;
	

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();
	//D�finition du Panel Compte Bancaire
	wxPanel* PanelCompteBancaire = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelCompteBancaire, wxID_ANY, wxBitmap("Compte.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	//Texte Bande Noir : pr�nom Nom | Num�ro
	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	Customer cust = client[r];
	Compte c(static_cast<string>(CompteNom), stoi(static_cast<string>(Montant)));
	cust.comptes_.push_back(c);
	client[r] = cust;
	this->client = client;
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money)+" �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money)+" �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;
	wxStaticText* TextUser = new wxStaticText(PanelCompteBancaire, USERINFORMATION, wxString::Format("%s | %d %s", cust.name_, code, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font

	
	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &CompteBancaire::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelCompteBancaire, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Texte Compte Bancaire
	wxStaticText* TextCompteBancaire = new wxStaticText(PanelCompteBancaire, COMPTEBANCAIRE, cust.comptes_[0].name, wxPoint(50, 145));
	wxFont fontCompte1 = TextCompteBancaire->GetFont();
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().MakeBold());
	TextCompteBancaire->SetFont(TextCompteBancaire->GetFont().Scale(1.1));
	//Texte Compte Cr�e 1
	wxStaticText* TextCompte1 = new wxStaticText(PanelCompteBancaire, COMPTE1, nomCompte1, wxPoint(50, 278));
	TextCompte1->SetFont(TextCompte1->GetFont().MakeBold());
	TextCompte1->SetFont(TextCompte1->GetFont().Scale(1.1));
	//Texte Compte Cr�e 2
	wxStaticText* TextCompte2 = new wxStaticText(PanelCompteBancaire, COMPTE2, nomCompte2, wxPoint(50, 353));
	TextCompte2->SetFont(TextCompte2->GetFont().MakeBold());
	TextCompte2->SetFont(TextCompte2->GetFont().Scale(1.1));

	//Texte Montant Compte Bancaire
	wxStaticText* TextMontantBancaire = new wxStaticText(PanelCompteBancaire, MONTANTBANCAIRE, to_string(cust.comptes_[0].money) + " �", wxPoint(530, 145));
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().MakeBold());
	TextMontantBancaire->SetFont(TextMontantBancaire->GetFont().Scale(1.1));
	//Texte Montant 1
	wxStaticText* TextMontant1 = new wxStaticText(PanelCompteBancaire, MONTANT1, montant1, wxPoint(530, 278));
	TextMontant1->SetFont(TextMontant1->GetFont().MakeBold());
	TextMontant1->SetFont(TextMontant1->GetFont().Scale(1.1));
	//Texte Montant 2
	wxStaticText* TextMontant2 = new wxStaticText(PanelCompteBancaire, MONTANT2, montant2, wxPoint(530, 353));
	TextMontant2->SetFont(TextMontant2->GetFont().MakeBold());
	TextMontant2->SetFont(TextMontant2->GetFont().Scale(1.1));

	//Texte Num�ro Compte Bancaire
	wxStaticText* TextNum�roCompteBancaire = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTEBANCAIRE, to_string(abs(num)), wxPoint(50, 178));
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().MakeBold());
	TextNum�roCompteBancaire->SetFont(TextNum�roCompteBancaire->GetFont().Scale(1.1));
	TextNum�roCompteBancaire->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompteBancaire->SetForegroundColour(wxColour(111, 111, 111)); //gris
	//Texte Num�ro Compte 1
	wxStaticText* TextNum�roCompte1 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE1, numero1, wxPoint(50, 311));
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().MakeBold());
	TextNum�roCompte1->SetFont(TextNum�roCompte1->GetFont().Scale(1.1));
	TextNum�roCompte1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte1->SetForegroundColour(wxColour(224, 52, 0)); //rouge
	//Texte Num�ro Compte 2
	wxStaticText* TextNum�roCompte2 = new wxStaticText(PanelCompteBancaire, NUMEROCOMPTE2, numero2, wxPoint(50, 386));
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().MakeBold());
	TextNum�roCompte2->SetFont(TextNum�roCompte2->GetFont().Scale(1.1));
	TextNum�roCompte2->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	TextNum�roCompte2->SetForegroundColour(wxColour(224, 52, 0)); //rouge

	//Bouton Valider
	wxButton* BtnValiderCreation = new wxButton(Fond, VALIDERCREATION, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderCreation->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderCreation->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderCreation->SetFont(BtnValiderCreation->GetFont().MakeBold());

	//Bouton Virement
	wxButton* BtnVirement = new wxButton(Fond, VIREMENT, "VIREMENT", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnVirement->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	BtnVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnVirement->SetFont(BtnVirement->GetFont().MakeBold());

	//Bouton Deconnexion
	wxButton* BtnDeconnexionCompte = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionCompte->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionCompte->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionCompte->SetFont(BtnDeconnexionCompte->GetFont().MakeBold());

	//Bouton Suppression Compte 
	BtnSuppression = new wxButton(Fond, SUPPRESSIONCOMPTE, "Suppression de compte", wxPoint(453, 307), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression->SetFont(BtnSuppression->GetFont().MakeBold());
	//Bouton Suppression Compte 1
	BtnSuppression1 = new wxButton(Fond, SUPPRESSIONCOMPTE1, "Suppression de compte", wxPoint(453, 382), wxSize(150, -1), wxBORDER_NONE);
	BtnSuppression1->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnSuppression1->SetForegroundColour(wxColor(226, 1, 11)); //rouge
	BtnSuppression1->SetFont(BtnSuppression1->GetFont().MakeBold());

	//Input compte
	InputCompteCreation = new wxTextCtrl(Fond, NOMCOMPTECREATION, "", wxPoint(690, 135), wxSize(250, 35));
	InputCompteCreation->SetFont(InputCompteCreation->GetFont().Scale(1.3));

	//Input Montant
	InputMontantCreation = new wxTextCtrl(Fond, MONTANTCOMPTECREATION, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantCreation->SetFont(InputMontantCreation->GetFont().Scale(1.3));
}
//--------------------------------------------------------------------------//
//                             VIREMENT & DEPOT                             //
//--------------------------------------------------------------------------//

//---------------- EVENEMENTS & METHODES ----------------//

wxBEGIN_EVENT_TABLE(Virement, wxDialog)
EVT_BUTTON(COMPTE, Virement::BtnCompte)
EVT_BUTTON(DECONNEXION, Virement::BtnDeconnexion)
EVT_BUTTON(VALIDERVIREMENT, Virement::BtnValiderVirement)
EVT_BUTTON(VALIDERDEPOT, Virement::BtnValiderDepot)
EVT_UPDATE_UI(VALIDERVIREMENT, Virement::VerificationVirement)
EVT_UPDATE_UI(VALIDERDEPOT, Virement::VerificationDepot)
wxEND_EVENT_TABLE()

//Fonction Ouvrir un nouveau panel 
void Virement::BtnCompte(wxCommandEvent& evt) {
	CompteBancaire* dlg = new CompteBancaire(client, codeclient, this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	Close();
	if (dlg->ShowModal() == VIREMENT) {  // Ouvrir le panel Compte Bancaire
	}
}

//Fonction Bouton Deconnexion de la session
void Virement::BtnDeconnexion(wxCommandEvent& evt) {
	Destroy();
}

//Fonction Bouton Valider Virement
void Virement::BtnValiderVirement(wxCommandEvent& evt) {
	Close();
	Virement* dlg = new Virement(client, codeclient, ChoixCompteVirement->GetStringSelection(), InputBeneficiaire->GetValue(), InputMontantVirement->GetValue(), this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	if (dlg->ShowModal() == VALIDERVIREMENT) {
	}
}

//Fonction Bouton Valider Depot
void Virement::BtnValiderDepot(wxCommandEvent& evt) {
	Close();
	Virement* dlg = new Virement(client, codeclient, InputMontantDepot->GetValue(), ChoixCompteDepot->GetStringSelection(), this, wxID_ANY, ("Soci�t� G�n�rale | Compte Bancaire"));
	if (dlg->ShowModal() == VALIDERDEPOT) {
	}
}

//V�rification donn�e virement
void Virement::VerificationVirement(wxUpdateUIEvent& event) {
	if (!InputMontantVirement->GetValue().IsNumber() || ChoixCompteVirement->GetStringSelection().IsEmpty() || InputMontantVirement->GetValue().empty() || InputBeneficiaire->GetValue().empty() || InputPourquoi->GetValue().empty()) {
		event.Enable(false);
		return;
	}
	event.Enable(true);
}



//V�rification donn�e depot
void Virement::VerificationDepot(wxUpdateUIEvent& event) {
	if (!InputMontantDepot->GetValue().IsNumber() || ChoixCompteDepot->GetStringSelection().IsEmpty() || InputMontantDepot->GetValue().empty()) {
		event.Enable(false);
		return;
	}
	event.Enable(true);
}

//---------------- DESIGN DU PANEL  ----------------//

Virement::Virement(vector<Customer> client, wxString codeclient, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;

	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();

	//Background du Panel
	wxPanel* PanelVirement = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelVirement, wxID_ANY, wxBitmap("Virement.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	Customer cust = client[r];
	this->client = client;
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money) + " �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money) + " �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;

	//Texte Bande Noir : pr�nom Nom | Num�ro
	wxStaticText* TextUser = new wxStaticText(PanelVirement, USERINFORMATION, wxString::Format("%s | %s %s", cust.name_, codeclient, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &Virement::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelVirement, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Bouton Deconnexion Virement
	wxButton* BtnDeconnexionVirement = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionVirement->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionVirement->SetFont(BtnDeconnexionVirement->GetFont().MakeBold());

	//Bouton Valider Virement
	wxButton* BtnValiderVirement = new wxButton(Fond, VALIDERVIREMENT, "VALIDER", wxPoint(38, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderVirement->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderVirement->SetFont(BtnValiderVirement->GetFont().MakeBold());

	//Bouton Valider Depot
	wxButton* BtnValiderDepot = new wxButton(Fond, VALIDERDEPOT, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderDepot->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderDepot->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderDepot->SetFont(BtnValiderDepot->GetFont().MakeBold());

	//Bouton Compte
	wxButton* BtnCompte = new wxButton(Fond, COMPTE, "MES COMPTES", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnCompte->SetBackgroundColour(wxColor(0, 0, 0)); //Noir
	BtnCompte->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnCompte->SetFont(BtnCompte->GetFont().MakeBold());

	//Input B�n�ficiaire
	InputBeneficiaire = new wxTextCtrl(Fond, BENEFICIAIRE, "", wxPoint(38, 217), wxSize(250, 35));
	InputBeneficiaire->SetFont(InputBeneficiaire->GetFont().Scale(1.3));

	//Input Montant Virement
	InputMontantVirement = new wxTextCtrl(Fond, MONTANTVIREMENT, "", wxPoint(325, 135), wxSize(250, 35));
	InputMontantVirement->SetFont(InputMontantVirement->GetFont().Scale(1.3));

	//Input Pourquoi
	InputPourquoi = new wxTextCtrl(Fond, POURQUOI, "", wxPoint(325, 217), wxSize(250, 35));
	InputPourquoi->SetFont(InputPourquoi->GetFont().Scale(1.3));

	//Input Montant1 Depot
	InputMontantDepot = new wxTextCtrl(Fond, MONTANTDEPOT, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantDepot->SetFont(InputMontantDepot->GetFont().Scale(1.3));

	//Choisir Compte
	wxArrayString choices;
	choices.Add(cust.comptes_[0].name);
	choices.Add(nomCompte1);
	choices.Add(nomCompte2);
	ChoixCompteVirement = new wxChoice(Fond, CHOIX, wxPoint(38, 135), wxSize(250, 155), choices); //Choix Virement
	ChoixCompteVirement->SetFont(ChoixCompteVirement->GetFont().Scale(1.5));
	ChoixCompteDepot = new wxChoice(Fond, CHOIX, wxPoint(690, 135), wxSize(250, 300), choices); //Choix Depot
	ChoixCompteDepot->SetFont(ChoixCompteDepot->GetFont().Scale(1.5));
}

Virement::Virement(vector<Customer>client, wxString codeclient, wxString CVirement, wxString Benef, wxString Montant, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;
	this->Beneficiaire = Benef;
	this->CompteVirement = CVirement;
	this->MontantVirement = Montant;
	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();

	//Background du Panel
	wxPanel* PanelVirement = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelVirement, wxID_ANY, wxBitmap("Virement.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	int r;
	int k;
	int code = stoi(static_cast<string>(codeclient));
	int code1 = stoi(static_cast<string>(Benef));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	for (int i = 0; i < client.size(); i++) {
		if (code1 == client[i].number_) {
			k = i;
		}
	}
	for (int x = 0; x < client[r].comptes_.size(); x++) {
		if (static_cast<string>(CVirement) == client[r].comptes_[x].name) {
			if(client[r].comptes_[x].money>= stoi(static_cast<string>(Montant))){
				client[r].comptes_[x].money -= stoi(static_cast<string>(Montant));
				client[k].comptes_[0].money += stoi(static_cast<string>(Montant));
			}
			else {
				wxMessageBox("Le virement est sup�rieur � la somme actuelle sur votre compte ", "Erreur", wxOK | wxICON_ERROR);
			}
		}
	}
	Customer cust = client[r];
	this->client = client;
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money) + " �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money) + " �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;

	//Texte Bande Noir : pr�nom Nom | Num�ro
	wxStaticText* TextUser = new wxStaticText(PanelVirement, USERINFORMATION, wxString::Format("%s | %s %s", cust.name_, codeclient, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &Virement::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelVirement, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Bouton Deconnexion Virement
	wxButton* BtnDeconnexionVirement = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionVirement->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionVirement->SetFont(BtnDeconnexionVirement->GetFont().MakeBold());

	//Bouton Valider Virement
	wxButton* BtnValiderVirement = new wxButton(Fond, VALIDERVIREMENT, "VALIDER", wxPoint(38, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderVirement->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderVirement->SetFont(BtnValiderVirement->GetFont().MakeBold());

	//Bouton Valider Depot
	wxButton* BtnValiderDepot = new wxButton(Fond, VALIDERDEPOT, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderDepot->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderDepot->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderDepot->SetFont(BtnValiderDepot->GetFont().MakeBold());

	//Bouton Compte
	wxButton* BtnCompte = new wxButton(Fond, COMPTE, "MES COMPTES", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnCompte->SetBackgroundColour(wxColor(0, 0, 0)); //Noir
	BtnCompte->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnCompte->SetFont(BtnCompte->GetFont().MakeBold());

	//Input B�n�ficiaire
	InputBeneficiaire = new wxTextCtrl(Fond, BENEFICIAIRE, "", wxPoint(38, 217), wxSize(250, 35));
	InputBeneficiaire->SetFont(InputBeneficiaire->GetFont().Scale(1.3));

	//Input Montant Virement
	InputMontantVirement = new wxTextCtrl(Fond, MONTANTVIREMENT, "", wxPoint(325, 135), wxSize(250, 35));
	InputMontantVirement->SetFont(InputMontantVirement->GetFont().Scale(1.3));

	//Input Pourquoi
	InputPourquoi = new wxTextCtrl(Fond, POURQUOI, "", wxPoint(325, 217), wxSize(250, 35));
	InputPourquoi->SetFont(InputPourquoi->GetFont().Scale(1.3));

	//Input Montant1 Depot
	InputMontantDepot = new wxTextCtrl(Fond, MONTANTDEPOT, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantDepot->SetFont(InputMontantDepot->GetFont().Scale(1.3));

	//Choisir Compte
	wxArrayString choices;
	choices.Add(cust.comptes_[0].name);
	choices.Add(nomCompte1);
	choices.Add(nomCompte2);
	ChoixCompteVirement = new wxChoice(Fond, CHOIX, wxPoint(38, 135), wxSize(250, 155), choices); //Choix Virement
	ChoixCompteVirement->SetFont(ChoixCompteVirement->GetFont().Scale(1.5));
	ChoixCompteDepot = new wxChoice(Fond, CHOIX, wxPoint(690, 135), wxSize(250, 300), choices); //Choix Depot
	ChoixCompteDepot->SetFont(ChoixCompteDepot->GetFont().Scale(1.5));
}

Virement::Virement(vector<Customer>client, wxString codeclient, wxString Montant, wxString CompteDep, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name) {

	//Variable
	this->codeclient = codeclient;
	this->MontantDepot = Montant;
	this->CompteDepot = CompteDep;
	//Setup
	SetIcon(wxIcon("icon.ico", wxBITMAP_TYPE_ICO));
	SetMinSize(wxSize(1000, 600));
	Fit();
	Center();

	//Background du Panel
	wxPanel* PanelVirement = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
	PanelVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc

	//Afficher l'image
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* Fond = new wxStaticBitmap(PanelVirement, wxID_ANY, wxBitmap("Virement.bmp", wxBITMAP_TYPE_BMP)); //Image Fond

	int r;
	int code = stoi(static_cast<string>(codeclient));
	for (int j = 0; j < client.size(); j++) {
		if (code == client[j].number_) {
			r = j;
		}
	}
	for (int x = 0; x < client[r].comptes_.size(); x++) {
		if (static_cast<string>(CompteDep) == client[r].comptes_[x].name) {
			client[r].comptes_[x].ajouter_Compte(static_cast<float>(stoi(static_cast<string>(Montant))));
		}
	}
	Customer cust = client[r];
	this->client = client;
	int num = cust.comptes_[0].numero_compte;
	string nomCompte1;
	string montant1;
	string numero1;
	int num1 = 0;
	if (cust.comptes_.size() >= 2) {
		nomCompte1 = cust.comptes_[1].name;
		montant1 = to_string(cust.comptes_[1].money) + " �";
		numero1 = to_string(abs(cust.comptes_[1].numero_compte));
	}
	else {
		nomCompte1 = "";
		montant1 = "";
		numero1 = "";
	}
	string nomCompte2;
	string montant2;
	string numero2;
	int num2 = 0;
	if (cust.comptes_.size() >= 3) {
		nomCompte2 = cust.comptes_[2].name;
		montant2 = to_string(cust.comptes_[2].money) + " �";
		numero2 = to_string(abs(cust.comptes_[2].numero_compte));
	}
	else {
		nomCompte2 = "";
		montant2 = "";
		numero2 = "";
	}
	this->prenom = cust.name_;
	this->adresse = cust.adresse;

	//Texte Bande Noir : pr�nom Nom | Num�ro
	wxStaticText* TextUser = new wxStaticText(PanelVirement, USERINFORMATION, wxString::Format("%s | %s %s", cust.name_, codeclient, cust.adresse), wxPoint(40, 7.5));
	TextUser->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextUser->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextUser->SetFont(TextUser->GetFont().MakeBold()); //Gras
	TextUser->SetFont(TextUser->GetFont().Scale(1.1)); //Taille font


	//Texte Bande Noir : Heure
	m_clockTimer.Bind(wxEVT_TIMER, &Virement::OnUpdateClock, this);
	m_clockTimer.Start(1000);
	TextHeure = new wxStaticText(PanelVirement, LIEUHEURE, "", wxPoint(832, 8));
	TextHeure->SetBackgroundColour(wxColor(0, 0, 0)); //noir
	TextHeure->SetForegroundColour(wxColour(255, 255, 255)); //blanc
	TextHeure->SetFont(TextHeure->GetFont().MakeBold());
	TextHeure->SetFont(TextHeure->GetFont().Scale(1.1));
	UpdateClock();

	//Bouton Deconnexion Virement
	wxButton* BtnDeconnexionVirement = new wxButton(Fond, DECONNEXION, "DECONNEXION", wxPoint(705, 466), wxSize(170, 30), wxBORDER_NONE);
	BtnDeconnexionVirement->SetBackgroundColour(wxColor(255, 255, 255)); //blanc
	BtnDeconnexionVirement->SetForegroundColour(wxColor(0, 0, 0)); //noir
	BtnDeconnexionVirement->SetFont(BtnDeconnexionVirement->GetFont().MakeBold());

	//Bouton Valider Virement
	wxButton* BtnValiderVirement = new wxButton(Fond, VALIDERVIREMENT, "VALIDER", wxPoint(38, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderVirement->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderVirement->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderVirement->SetFont(BtnValiderVirement->GetFont().MakeBold());

	//Bouton Valider Depot
	wxButton* BtnValiderDepot = new wxButton(Fond, VALIDERDEPOT, "VALIDER", wxPoint(690, 280), wxSize(200, 40), wxBORDER_NONE);
	BtnValiderDepot->SetBackgroundColour(wxColor(226, 1, 11)); //rouge
	BtnValiderDepot->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnValiderDepot->SetFont(BtnValiderDepot->GetFont().MakeBold());

	//Bouton Compte
	wxButton* BtnCompte = new wxButton(Fond, COMPTE, "MES COMPTES", wxPoint(690, 340), wxSize(200, 40), wxBORDER_NONE);
	BtnCompte->SetBackgroundColour(wxColor(0, 0, 0)); //Noir
	BtnCompte->SetForegroundColour(wxColor(255, 255, 255)); //blanc
	BtnCompte->SetFont(BtnCompte->GetFont().MakeBold());

	//Input B�n�ficiaire
	InputBeneficiaire = new wxTextCtrl(Fond, BENEFICIAIRE, "", wxPoint(38, 217), wxSize(250, 35));
	InputBeneficiaire->SetFont(InputBeneficiaire->GetFont().Scale(1.3));

	//Input Montant Virement
	InputMontantVirement = new wxTextCtrl(Fond, MONTANTVIREMENT, "", wxPoint(325, 135), wxSize(250, 35));
	InputMontantVirement->SetFont(InputMontantVirement->GetFont().Scale(1.3));

	//Input Pourquoi
	InputPourquoi = new wxTextCtrl(Fond, POURQUOI, "", wxPoint(325, 217), wxSize(250, 35));
	InputPourquoi->SetFont(InputPourquoi->GetFont().Scale(1.3));

	//Input Montant1 Depot
	InputMontantDepot = new wxTextCtrl(Fond, MONTANTDEPOT, "", wxPoint(690, 220), wxSize(250, 35));
	InputMontantDepot->SetFont(InputMontantDepot->GetFont().Scale(1.3));

	//Choisir Compte
	wxArrayString choices;
	choices.Add(cust.comptes_[0].name);
	choices.Add(nomCompte1);
	choices.Add(nomCompte2);
	ChoixCompteVirement = new wxChoice(Fond, CHOIX, wxPoint(38, 135), wxSize(250, 155), choices); //Choix Virement
	ChoixCompteVirement->SetFont(ChoixCompteVirement->GetFont().Scale(1.5));
	ChoixCompteDepot = new wxChoice(Fond, CHOIX, wxPoint(690, 135), wxSize(250, 300), choices); //Choix Depot
	ChoixCompteDepot->SetFont(ChoixCompteDepot->GetFont().Scale(1.5));
}
