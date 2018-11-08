#include "two-three.h"
#include "time.h"
#include <iomanip>
#include <sstream>

// constructor
TTT::TTT(){
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TTT::isEmpty(){
    return root = NULL;
}
void TTT::printTree(ostream & out) const {
	out << "Two Three Tree Index:\n-------------------------\n";
	printTreeHelper(root, out);
}
void TTT::buildTree(ifstream & input){
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord; // Templine is where the string will be stored, char by char

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
		    //Insert valid chars into tempWord until a delimiter( newline or space) is found
		    while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
			tempWord.insert(tempWord.end(), tempLine[i]);
			i++;
		    }
		   
            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
			    tempWord.resize(tempWord.size() -1);   
			
            if (tempWord.length() > 0)
            {
                //Once word is formatted, call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                insertHelper(tempWord, line, root, distWords);
                //Increment our total number of words inserted
                numWords++;
                //Clear out tempWord so we can use it again
                tempWord.clear();
		    }
			
		}
		line++;
	}
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
	//treeHeight = findHeight(root);

	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords<< endl;

	cout << setw(40) << std::left 
	<< "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left 
	<<"Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
	<<"Height of 2-3 is : " << treeHeight << endl;
 
}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TTT::insertHelper(const string &x, int line, node *& t, int &distWord){
    if(t == NULL)
    {
	    t = new node(x, "","","", NULL, NULL, NULL);
	    t->lines.push_back(line);
	    distWord++;
    }
    else 
    {
    if (x.compare(t->key) > 0 && t->left != NULL)
        insertHelper(x, line, t->left, distWord);
    
    else if (x.compare(t->key) < 0 && t->right != NULL)
        insertHelper(x, line, t->right, distWord);
    
	else if (x.compare(t->lval) > 0 && t->left == NULL){
        if (t->lval != "" && t->rval != ""){
            node * r = new node("","", x, "", NULL, NULL, NULL);
            node * l = new node("", "",t->rval, "", NULL, NULL, NULL);
            t->left = r->middle;
            r->middle = t->left;
            t->right = l->middle;
            l->middle = t->right;
            t->mval = t->rval;
            t->lval = "";
            t->rval = "";
        }
        else{
        t->rval = t->key; // Move the root to the right
        t->lval = x; // Insert new key to the left value
        t->key = "";
        }
    }
    	else if (x.compare(t->lval) < 0 && t->left == NULL){
        if (t->lval != "" && t->rval != ""){
            node * r =  new node("","", t->rval, "", NULL, t->left, NULL);
            node * l =  new node("", "",x, "", NULL, t->right, NULL);
            t->left = r->middle;
            r->middle = t->left;
            t->right = l->middle;
            l->middle = t->right;
            t->mval = t->lval;
            t->lval = "";
            t->rval = "";
            // stop here
        }
        else{
        t->rval = t->key; // Move the root to the right
        t->lval = x; // Insert new key to the left value
        t->key = "";
        }
    }
    //insertHelper(x, line, t->right, distWord);
	else if (x.compare(t->key) == 0)
	    t->lines.push_back(line);
	else if (x.compare(t->rval) < 0 && t->right == NULL){ // if (x < key) then < 0
        t->lval = t->key; // Move the root to the right
        t->rval = x; // Insert new key to the left value
        t->key = "";
    }
    //insertHelper(x, line, t->left, distWord);
			
    }
}

void TTT::printTreeHelper(node *t, ostream & out) const{
    if(t == NULL)
		return;
	else {
		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->key << " " << t->lines[0];
		for (int i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
		printTreeHelper(t->right, out);
	}
}