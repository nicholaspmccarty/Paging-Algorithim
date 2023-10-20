// Nicholas McCarty
// CSE 381
// Paging 

#include <iostream>
#include <array>
#include <vector>
#include <unordered_set>
#include <random>
inline constexpr int kNumFrames(3);
inline constexpr int kNumVirtualPages(10);

struct FrameQueue {
    std::array<int, kNumFrames> data;
    int head;
    uint32_t size;

    FrameQueue() {
        size = 0;
        head = 0;
    }
};

// A simple method that returns the position in the queue.
int queuePosition(const FrameQueue& queue, int element) {
    int ret = -1; // Initialize ret to -1 to indicate the element was not found
    for (size_t j = 0; j < queue.size; j++) {
         if (queue.data[j] == element) {
            ret = static_cast<int>(j);
            break;
         }
    }
    return ret;

    // end of scope
}
// A simple method that prints the queue.
std::string print(const FrameQueue& queue) {
    std::string result = "\t";
    for (uint32_t i = 0; i < queue.size; ++i) {
        int c = queue.data[i];
        if (c >= 0) {
            result += std::to_string(c);
        }
        result += ",";
    }
    result += "\t";

    // TODO Print the queue in page lookup table format

    // end of scope
    
    return result;
}


// A method that replaces the head of thte queue.
void replaceHead(FrameQueue& queue, int element) {
   queue.data[static_cast<size_t>(queue.head)] = element;
   queue.head = (queue.head + 1) % kNumFrames;
   
   if (queue.size <= 2) {
    ++queue.size;
   }
   // end of scope
}



// This will help us go hrough the queue and check each elements.
bool queryQueue(FrameQueue& queue, int page) {
    if (queuePosition(queue, page) != -1) {
        // Page is already in the queue (Hit)
        return true;
    } else {
        // Page is not in the queue (Miss)
        print(queue);
        replaceHead(queue, page);
        // return false
        return false;
    }

    // end of scope
}
void printPLT(FrameQueue queue) {
        for (int i = 0; i < kNumVirtualPages; ++i) {
        if (i > 0) {
            std::cout << ",";
        }
        if (queuePosition(queue, i) != -1) {
            std::cout << queuePosition(queue, i);
        } 
    }
    std::cout << std::endl;
}


bool workingSet(FrameQueue& queue, int page) {
    std::unordered_set<int> W;
    if (queuePosition(queue, page) != -1) {
        return true;
    } else {
        // Page is not in the queue (Miss)
        print(queue);
     for (size_t i = 0; i < static_cast<size_t>(queue.size); i++) {
            W.insert(queue.data[i]);
        }
        // Add randomly to the working set from set_difference until it's full or difference is empty
        while (W.size() < 3) {
            int randomPage = rand() % kNumVirtualPages;  // Generate a random page in the range
            if (W.find(randomPage) == W.end()) {
                W.insert(randomPage);
            }
        }
        // Update the queue with the new working set
        queue.size = 0;
        for (int p : W) {
            queue.data[queue.size] = p;
            queue.size++;
        }
        return false;
    }
}

std::vector<int> generateUniformRandomData(int n, int min, int max) {
    std::vector<int> data;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min, max);
    
    for (int i = 0; i < n; ++i) {
        data.push_back(distribution(generator));
    }
    
    return data;
}

std::vector<int> generateNormalDistribution(int n, double mean, double max) {
    std::vector<int> data;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mean, max);

    for (int i = 0; i < n; ++i) {
        data.push_back(static_cast<int>(distribution(generator)));
    }
        return data;
}

std::vector<int> generateUniformTime(int n, int min, int max) {
    std::vector<int> data;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    
    for (int i = 0; i < n; ++i) {
        data.push_back(distribution(generator));
    }
    
    return data;
}

std::vector<int> generateWorstCase(int n) {
    std::vector<int> data;
    for (int i = 0; i < n; ++i) {
        data.push_back(i % 3);
    }
    return data;
}

std::vector<int> generateNormalTime(int n, double mean, double max) {
    std::vector<int> data;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<double> distribution(mean, max);

    for (int i = 0; i < n; ++i) {
        data.push_back(static_cast<int>(distribution(generator)));
    }
        return data;
}



void printHeader() {
   std::cout << "====================================" << std::endl;
    std::cout << "          IMPORTANT NOTICE          " << std::endl;
    std::cout << "====================================" << std::endl;
}

void printFooter() {
    std::cout << "====================================" << std::endl;
    std::cout << "  PLEASE SEE SEPARATE DOCUMENT FOR  " << std::endl;
    std::cout << "          SUBMITTED GRAPHS          " << std::endl;
    std::cout << "====================================" << std::endl;
}
int main() {
    int n = 10; 
    int min = 0; 
    int max = 9; 
    (void) n;
    (void) min;
    (void) max;
    double mean = (min + max) / 2.0; // Mean
    double stddev = 2.0;
    (void) stddev;
    (void) mean;
    printHeader();
    printFooter();
    FrameQueue queue;
    FrameQueue queue2;
    FrameQueue queue3;
    FrameQueue queue4;
    FrameQueue queue5;
    FrameQueue tester;
    std::vector<int> queries = { 1,5,3,0,2,3,2,0,1 };
    std::vector<int> input = {8,8,6,2,5,2,1,5,2,4};
    // std::cout << "input: {";
    /*
    
    for (uint32_t i = 0; i < queries.size(); ++i) {
        std::cout << queries[i];
        if (i < queries.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";

    std::cout << "Hit?\tFIFO\tPLT\n";
    for (auto page_query : input) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(queue, page_query)) ? "Hit! " : "Miss! ");
        std::cout << print(queue);
        printPLT(queue);
    }
    
    
    std::cout << "Second test" << std::endl;

     for (uint32_t i = 0; i < input.size(); ++i) {
        std::cout << input[i];
        if (i < input.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << "Hit?\tFIFO\tPLT\n";
    for (auto page_query : input) {
        // TODO Check Boundary Conditions
        std::cout << ((queryQueue(queue, page_query)) ? "Hit! " : "Miss! ");
        std::cout << print(queue);

    }

    std::cout << "Testing working set" << std::endl;
     for (auto page_query : input) {
        // TODO Check Boundary Conditions
        std::cout << ((workingSet(queue, page_query)) ? "Hit! " : "Miss! ");
        std::cout << print(queue);
        printPLT(queue);
        std::cout << std::endl;

    } 
    */
   std::string dottedLine(40, '.');
    std::cout << dottedLine << std::endl;
    std::cout << "Here are our lists:" << std::endl;
    std::cout << dottedLine << std::endl;
    std::vector<int> test2 = generateUniformRandomData(n, min, max);
    std::vector<int> test = generateNormalDistribution(n, mean, stddev);
    std::vector<int> test3 = generateUniformTime(n, min, max);
    std::vector<int> test4 = generateNormalTime(n, mean, stddev);
    std::vector<int> test5 = generateWorstCase(n);
      std::cout << "Uniform: ";
      for (uint32_t i = 0; i < test2.size(); ++i) {
        std::cout << test2[i];
        if (i < test2.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "\n Normal: ";
     for (uint32_t i = 0; i < test.size(); ++i) {
        std::cout << test[i];
        if (i < test.size() - 1) {
            std::cout << ",";
        }
    }


    std::cout << "\nUniform time (change each time)" << std::endl;
    for (uint32_t i = 0; i < test3.size(); ++i) {
        std::cout << test3[i];
        if (i < test3.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "\nNormal time (change each time)" << std::endl;
    for (uint32_t i = 0; i < test4.size(); ++i) {
        std::cout << test4[i];
        if (i < test4.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
     std::cout << "Worst Case (changes each time as well): " << std::endl;
    for (uint32_t i = 0; i < test4.size(); ++i) {
        std::cout << test4[i];
        if (i < test4.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
    std::cout << dottedLine << std::endl;
    std::cout << "First we shall test Uniform Random data with FIFO and working set" << std::endl;
    std::cout << dottedLine << std::endl;
     std::cout << "Values: {";
    
    
    for (uint32_t i = 0; i < test2.size(); ++i) {
        std::cout << test2[i];
        if (i < test2.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << dottedLine << std::endl;
    for (auto page_query : test2) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(queue, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue);
        printPLT(queue);
    }
    for (auto page_query : test2) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((workingSet(queue2, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue2);
        printPLT(queue2);
    }
     
    std::cout << dottedLine << std::endl;
    std::cout << "Testing the second:{";
    for (uint32_t i = 0; i < test.size(); ++i) {
        std::cout << test[i];
        if (i < test.size() - 1) {
            std::cout << ",";
        }
    }
     std::cout << "}\n";
    std::cout << dottedLine << std::endl;
     for (auto page_query : test) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(queue3, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue3);
        printPLT(queue3);
        std::cout << ((workingSet(queue3, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue3);
        printPLT(queue3);

    }
    std::cout << dottedLine << std::endl;
    std::cout << "Testing the third:{";
    for (uint32_t i = 0; i < test3.size(); ++i) {
        std::cout << test3[i];
        if (i < test3.size() - 1) {
            std::cout << ",";
        }
    }
     std::cout << "}\n";
    std::cout << dottedLine << std::endl;
     for (auto page_query : test3) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(queue4, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue4);
        printPLT(queue4);
        std::cout << ((workingSet(queue4, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue4);
        printPLT(queue4);
    }
        std::cout << dottedLine << std::endl;
    std::cout << "Testing the fourth:{";
    for (uint32_t i = 0; i < test4.size(); ++i) {
        std::cout << test4[i];
        if (i < test4.size() - 1) {
            std::cout << ",";
        }
    }
     std::cout << "}\n";
    std::cout << dottedLine << std::endl;
     for (auto page_query : test4) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(queue5, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue5);
        printPLT(queue5);
        std::cout << ((workingSet(queue5, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(queue5);
        printPLT(queue5);
    }
        std::cout << dottedLine << std::endl;
    std::cout << "Testing the fifth:{";
    for (uint32_t i = 0; i < test5.size(); ++i) {
        std::cout << test5[i];
        if (i < test5.size() - 1) {
            std::cout << ",";
        }
    }
     std::cout << "}\n";
    std::cout << dottedLine << std::endl;
     for (auto page_query : test3) {
        // TODO Check Boundary Conditions
        if (page_query >= 10) {
            std::cout << "Error " << page_query << " is out of range" << std::endl;
            break;
            } else if (page_query <= -1) {
                std::cout << "Error " << page_query << " is out of range" << std::endl;
            
            }
        std::cout << ((queryQueue(tester, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(tester);
        printPLT(tester);
        std::cout << ((workingSet(tester, page_query)) ? "OKAY " : "Fault ");
        std::cout << print(tester);
        printPLT(tester);
    }

    std::cout << dottedLine << std::endl;
    std::cout << "It's important to note the first ten each are FIFO - then the following ten are working set. Enjoy:)" << std::endl;
    printHeader();
    printFooter();
    
   

    

    

    // All test cases have been met, and compiler passes.
    // End of scope
    


    return 0;

}

