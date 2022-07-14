// Created by fahee on 6/21/2022.
//

#include "Document_parser.h"

Document_parser::Document_parser(AVLTree<string, Article>* tree1,AVLTree<string, Article>* tree2,AVLTree<string, Article>* tree3) {
    stop_words = {"able", "about", "above", "abroad", "according", "accordingly", "across",
                  "actually", "adj", "after", "afterwards", "again", "against", "ago", "ahead",
                  "ain't", "all", "allow", "allows", "almost", "alone", "along", "alongside",
                  "already", "also", "although", "always", "am", "amid", "amidst", "among",
                  "amongst","an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything",
                  "anyway", "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate",
                  "are", "aren't", "around", "as", "a's", "aside", "ask", "asking", "associated",
                  "at", "available", "away", "awfully", "back", "backward", "backwards", "be",
                  "became", "because", "become", "becomes", "becoming", "been", "before",
                  "beforehand", "begin", "behind", "being", "believe", "below", "beside",
                  "besides", "best", "better", "between", "beyond", "both", "brief", "but", "by",
                  "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes",
                  "certain", "certainly",
                  "changes", "clearly", "c'mon", "co", "co.", "com", "come", "comes",
                  "concerning", "consequently", "consider", "considering", "contain",
                  "containing", "contains", "corresponding", "could", "couldn't", "course", "c's",
                  "currently", "dare", "daren't", "definitely", "described", "despite", "did",
                  "didn't", "different", "directly",
                  "do", "does", "doesn't", "doing", "done", "don't", "down", "downwards",
                  "during", "each", "edu", "eg", "eight", "eighty", "either", "else", "elsewhere",
                  "end", "ending", "enough", "entirely", "especially", "et", "etc", "even",
                  "ever", "evermore", "every", "everybody", "everyone", "everything",
                  "everywhere",
                  "ex", "exactly", "example", "except", "fairly", "far", "farther", "few",
                  "fewer", "fifth", "first", "five", "followed", "following", "follows", "for",
                  "forever", "former", "formerly", "forth", "forward", "found", "four", "from",
                  "further", "furthermore", "get", "gets", "getting", "given", "gives", "go",
                  "goes",
                  "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half",
                  "happens", "hardly", "has", "hasn't", "have", "haven't", "having", "he", "he'd",
                  "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby",
                  "herein", "here's", "hereupon", "hers", "herself", "he's", "hi", "him",
                  "himself", "his",
                  "hither", "hopefully", "how", "howbeit", "however", "hundred", "i'd", "ie",
                  "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.",
                  "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar",
                  "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its",
                  "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known",
                  "knows", "last", "lately", "later", "latter", "latterly", "least", "less",
                  "lest", "let", "let's", "like", "liked", "likely", "likewise", "little", "look",
                  "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make", "makes",
                  "many", "may", "maybe", "mayn't", "me", "mean", "meantime", "meanwhile",
                  "merely", "might", "mightn't", "mine", "minus", "miss", "more", "moreover",
                  "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my", "myself",
                  "name", "namely", "nd", "near", "nearly", "necessary",
                  "need", "needn't", "needs", "neither", "never", "neverf", "neverless",
                  "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none",
                  "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing",
                  "notwithstanding", "novel", "now", "nowhere", "obviously",
                  "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones",
                  "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise",
                  "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over",
                  "overall", "own", "particular", "particularly", "past",
                  "per", "perhaps", "placed", "please", "plus", "possible", "presumably",
                  "probably", "provided", "provides", "que", "quite", "qv", "rather", "rd", "re",
                  "really", "reasonably", "recent", "recently", "regarding", "regardless",
                  "regards", "relatively", "respectively", "right", "round",
                  "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see",
                  "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves",
                  "sensible", "sent", "serious", "seriously", "seven", "several", "shall",
                  "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't",
                  "since", "six", "so", "some", "somebody", "someday", "somehow", "someone",
                  "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry",
                  "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure",
                  "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks",
                  "thanx",
                  "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs",
                  "them", "themselves", "then", "thence", "there", "thereafter", "thereby",
                  "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's",
                  "thereupon", "there've", "these", "they", "they'd", "they'll", "they're",
                  "they've",
                  "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly",
                  "those", "though", "three", "through", "throughout", "thru", "thus", "till",
                  "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly",
                  "try", "trying", "t's", "twice", "two", "un", "under", "underneath", "undoing",
                  "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon",
                  "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v",
                  "value", "various", "versus", "very", "via", "viz", "vs", "want", "wants",
                  "was", "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went",
                  "were", "we're", "weren't",
                  "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence",
                  "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's ",
                  "whereupon", "wherever", "whether", "which", "whichever", "while", "whilst",
                  "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever",
                  "who's",
                  "whose", "why", "will", "willing", "wish", "with", "within", "without",
                  "wonder", "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll",
                  "your", "you're", "yours", "yourself", "yourselves", "you've", "zero"};
    text_clear = tree1;
    people =tree2;
    org= tree3;


}

void Document_parser::read_files(const string& filename) {
    ifstream file;
    file.open(filename);

    IStreamWrapper isw(file);

    Document documents;
    documents.ParseStream(isw);

    Article current;
    current.filename = filename;
    current.title = documents["title"].GetString();
    current.uuid = documents["uuid"].GetString();
    current.full_text = documents["text"].GetString();
// Get the id

    //Getting the person
    for (auto &p: documents["entities"]["persons"].GetArray()) {
        string person = p["name"].GetString();
        for (int i = 0; i < person.size(); i++) {
            person[i] = ::tolower(person[i]);
        }
        char str[person.length() +1];
        strcpy(str,person.c_str());

        char* token_words;
        token_words = strtok(str," ");

        while(token_words != nullptr){
            string token_string = token_words;
            //adding the people to the AVL tree
            people->insert(token_string,current);

            //update it that way out of loop maybe?
            token_words = strtok(nullptr," ");
        }

    }

    //Getting organizations
    for (auto &p: documents["entities"]["organizations"].GetArray()) {
        string organization = p["name"].GetString();
        for (int i = 0; i < organization.size(); i++) {
            organization[i] = ::tolower(organization[i]);
        }
        char str[organization.length() +1];
        strcpy(str,organization.c_str());

        char* token_words;
        token_words = strtok(str," ");

        while(token_words != nullptr){
            string token_string = token_words;
            //adding the organization to the AVL tree
            org->insert(token_string,current);

            //update it that way out of loop maybe?
            token_words = strtok(nullptr," ");
        }

    }


    string texts = documents["text"].GetString();
    cleaning_data(texts,current);

}
void Document_parser::files_system(const string& paths){
    for(const auto& entry : fs::recursive_directory_iterator(paths)){
        if(entry.is_regular_file() && entry.path().extension().string() == ".json"){
            string file_name = entry.path().c_str();
            read_files(file_name);
            file_names.push_back(file_name);
            numDocsParsed++;
        }
    }
}

void Document_parser::cleaning_data(string text, Article& a) {
// tokenize the text to split it, and then basically
// iterate through the tokenized words and then stem each word, and stem the stop words, and then add it to the avl tree
// if text does not belong to the stop words then add to the tree
// string (text and the article)
//then call the remove words and

    char trash[]=" 1234567890+!@#$%^&*()~+={}[],.<>?;'|`";
    char str[text.length() +1]; // or will it be just length??
    strcpy(str, text.c_str());

    char* token_words;
    token_words = strtok(str,trash);

    while(token_words != nullptr){
        string token_string = token_words;

        Porter2Stemmer::trim(token_string);
        Porter2Stemmer::stem(token_string);

        if(stop_words.find(token_string)== stop_words.end()){
            a.words++; // total count of words in this article
            //insert the token string to the text in the AVL tree?
            text_clear->insert(token_string, a);
        }
        else{
            //just remove and ignore them
        }

        //update it that way out of loop maybe?
        token_words = strtok(nullptr,trash);
    }
}

int Document_parser::getTotalParsed() {
    return numDocsParsed;
}


