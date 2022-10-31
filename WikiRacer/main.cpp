#include <filesystem>  // making inputting files easier
#include <fstream>     // for ifstream
#include <iostream>    // for cout, cin
#include <queue>
#include <sstream>  // for stringstream
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "wikiscraper.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/*
 * This is the function you will be implementing parts of. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */

// TODO: ASSIGNMENT 2 TASK 5:
// Please implement the following function, which should take in two sets of
// strings and returns the number of common strings between the two sets. You
// should use lambdas and std::count_if. Estimated length: <4 lines

///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN STUDENT CODE HERE
int numCommonLinks(const unordered_set<string>& curr_set,
                   const unordered_set<string>& target_set) {
    int num = 0;
    for (auto& s : target_set) {
        if (curr_set.find(s) != curr_set.end()) {
            num++;
        }
    }
    return num;
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    WikiScraper w;
    /* Create alias for container backing priority_queue */
    using container = vector<vector<string>>;
    unordered_set<string> target_set = w.getLinkSet(end_page);

    // TODO: ASSIGNMENT 2 TASK 6:
    // Please implement the comparator function that will be used in the
    // priority queue. You'll need to consider what variables this lambda will
    // need to capture, as well as what parameters it'll take in. Be sure to use
    // the function you implemented in Task 1! Estimated length: <3 lines

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE
    auto cmp_fn = [&w, &target_set](const vector<string>& left,
                                    const vector<string>& right) {
        int num_left = numCommonLinks(target_set, w.getLinkSet(left.back()));
        int num_right = numCommonLinks(target_set, w.getLinkSet(right.back()));
        return num_left < num_right;
    };
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO: ASSIGNMENT 2 TASK 7:
    // Last exercise! please instantiate the priority queue for this algorithm,
    // called "queue". Be sure to use your work from Task 2, cmp_fn, to
    // instantiate our queue. Estimated length: 1 line

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE
    std::priority_queue<vector<string>, vector<vector<string>>, decltype(cmp_fn)> queue(
        cmp_fn);
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    queue.push({start_page});
    unordered_set<string> visited;

    while (!queue.empty()) {
        vector<string> curr_path = queue.top();
        queue.pop();
        string curr = curr_path.back();

        auto link_set = w.getLinkSet(curr);

        /*
         * Early check for whether we have found a ladder.
         * By doing this check up here we spead up the code because
         * we don't enqueue every link on this page if the target page
         * is in the links of this set.
         */
        if (link_set.find(end_page) != link_set.end()) {
            curr_path.push_back(end_page);
            return curr_path;
        }

        for (const string& neighbour : link_set) {
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                vector<string> new_path = curr_path;
                new_path.push_back(neighbour);
                queue.push(new_path);
            }
        }
    }
    return {};
}

int main() {
    // a quick working directory fix to allow for easier filename inputs
    auto path = std::filesystem::current_path() / "res/";
    std::filesystem::current_path(path);
    std::string filenames = "Available input files: ";

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string filename = entry.path().string();
        filename = filename.substr(filename.rfind("/") + 1);
        filenames += filename + ", ";
    }
    // omit last ", ".
    cout << filenames.substr(0, filenames.size() - 2) << "." << endl;

    /* Container to store the found ladders in */
    vector<vector<string>> outputLadders;

    cout << "Enter a file name: ";
    string filename;
    getline(cin, filename);
    /*
        TODO: Create a filestream from the filename.
        For each pair {start_page, end_page} in the input file,
        retrieve the result of findWikiLadder(start_page, end_page)
        and append that vector to outputLadders.
    */
    // Write code here
    ifstream ifs(filename, ifstream::in);
    int      pair_nums;
    string   start_page, end_page;

    ifs >> pair_nums;

    for (int i = 0; i < pair_nums; ++i) {
        ifs >> start_page >> end_page;
        outputLadders.push_back(findWikiLadder(start_page, end_page));
    }
    /*
     * Print out all ladders in outputLadders.
     * We've already implemented this for you!
     */
    // Write code here
    for (auto& ladder : outputLadders) {
        if (ladder.empty()) {
            cout << "No ladder found" << endl;
        } else {
            cout << "Ladder found:" << endl;
            cout << "\t{";
            std::copy(ladder.begin(), ladder.end() - 1,
                      std::ostream_iterator<string>(cout, " -> "));

            cout << ladder.back() << "}" << endl;
        }
    }
    return 0;
}