//
// Created by Nathan Hon on 6/23/2022.
//

#include "User_interface.h"

User_interface::User_interface() {
    createNewTrees();
}

void User_interface::createNewTrees() {
    tree1 = new AVLTree<string, Article>;  //text
    tree2 = new AVLTree<string, Article>;  //people
    tree3 = new AVLTree<string, Article>;  //Org

}

void User_interface::menuOptions() {
    string selection = "";

    cout << "Welcome to Financial News Search!" << endl;
    cout << "Please select from the following options(1-5): " << endl;
    cout << "1: Parse Documents" << endl;
    cout << "2: Enter Query" << endl;
    cout << "3: Get Statistics" << endl;
    cout << "4: Clear Index" << endl;
    cout << "5: Exit" << endl;

    getline(cin,selection);

    if (selection == "1")
        parseFiles();
    else if (selection == "2")
        enterQuery();
    else if (selection == "3")
        displayStats();
    else if (selection == "4")
        clearIndex();
    else if (selection == "5") {
        cout << endl << "Thank you for visiting Financial News Search, goodbye." << endl;
        return;
    } else {
        cout << "Incorrect input, please try again." << endl << endl;
        menuOptions();
    }

}

void User_interface::parseFiles() {
    // prompt user to enter directory
    cout << "Please enter directory path: ";
    string userDirectory = "";
    getline(cin,userDirectory);

    // create document parser object and pass in path from user input
    Document_parser p(tree1, tree2, tree3);
    p.files_system(userDirectory);
    totalDocsParsed = p.getTotalParsed();

    // when parse complete
    cout << "Parse complete." << endl << endl;
    menuOptions(); // return to menu
}

void User_interface::enterQuery() {
    vector<Article> articleVec;
    string query = "";
    string selection = "";
    string dummy;
    int page = 1;
    int fileNum = 0;
    string nextPage = "";
    string specFile = "";
    Query_processor q(tree1, tree2, tree3);
    cout << "Please input query:";
    getline(cin, query);

    results = q.parseQuery(query);

    // call function1 from Relevancy_ranking
    Relevancy_ranking rank;
    articleVec = rank.sortRanking(results, totalDocsParsed);

    for(int i = 0; i < articleVec.size(); i++){
        cout << " File " << i + 1 << ": " << articleVec[i].title << endl; // outputs numbered list with title of article
        if ((i + 1) % 15 == 0) {
            cout << endl << "Page <" << page << ">" << endl << endl;
            // prompt user for next page
            if ((i + 2) <= articleVec.size()) {
                cout << endl << "Would you like to open a specific file?(Y/N): ";
                cin >> specFile;
                if (specFile == "y" || specFile == "Y") {
                    cout << "Please enter file number: ";
                    cin >> fileNum;
                    cout << articleVec[i].full_text << endl << endl;
                }

                cout << "Continue to next page(Y/N): ";
                cin >> nextPage;

                // determine if user wants to go to next page or return to menu
                if (nextPage == "y" || nextPage == "Y") {
                    page++;
                    continue;
                } else {
                    // return to menu
                    break;
                }
            }
        } else if ((i + 1) == articleVec.size() && i < 14) {
            cout << endl << "Would you like to open a specific file?(Y/N): ";
            cin >> specFile;
            if (specFile == "y" || specFile == "Y") {
                cout << "Please enter file number: ";
                cin >> fileNum;
                 cout << articleVec[i].full_text << endl << endl;
            } else {
                break;
            }
//            break;
        }

    }
    cout << endl;
    getline(cin, dummy);
    menuOptions();
}

void User_interface::displayStats() {
    cout << "Total Documents Parsed: " << totalDocsParsed << endl;
    cout << "Number of Times Unique Words Appeared in the Parsed Files: " << tree1->getSize() << endl;
    cout << endl;
    //documents containing the word that was entered;
    //Access tree1 which has the text.
    // Need to access the pair to know both int vales for the stats.
    menuOptions();
}

void User_interface::clearIndex() {
    delete tree1;
    delete tree2;
    delete tree3;
    cout << "Index cleared" << endl << endl;

    createNewTrees();

    menuOptions(); // return to menu
}

