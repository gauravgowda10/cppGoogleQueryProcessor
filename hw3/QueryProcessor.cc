/*
 * Copyright ©2022 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

static list<DocIDElementHeader> MergeResults
    (const list<DocIDElementHeader>&, const list<DocIDElementHeader>&);

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;

  for (int i = 0; i < array_len_; i++) {
    DocTableReader* dtr = dtr_array_[i];
    IndexTableReader* itr = itr_array_[i];
    list<DocIDElementHeader> result;

    DocIDTableReader* didtr = itr->LookupWord(query[0]);
    if (didtr == NULL) {
      continue;
    }
    result = didtr->GetDocIDList();
    printf("The size of the result list is: %u \n", result.size());
    delete didtr;

    for (int j = 1; j < query.size(); j++) {
      list<DocIDElementHeader> partial_result;

      didtr = itr->LookupWord(query[j]);
      if (didtr == NULL) {
        result.clear();
        delete didtr;
        break;
      }
      partial_result = didtr->GetDocIDList();
      result = MergeResults(result, partial_result);
      delete didtr;
    }
    if (result.size() == 0) {
      continue;
    }
    list<DocIDElementHeader>:: iterator it;
    for (auto const& curr : result) {
      QueryResult curr_result;
      Verify333(dtr->LookupDocID(curr.doc_id, &curr_result.document_name));
      curr_result.rank = curr.num_positions;
      final_result.push_back(curr_result);
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

static list<DocIDElementHeader> MergeResults
       (const list<DocIDElementHeader> &list1,
       const list<DocIDElementHeader> &list2) {
  list<DocIDElementHeader> list_final;

  for (auto const& i : list1) {
    int32_t num_positions = i.num_positions;

    for (auto const& j : list2) {
      if (j.doc_id == i.doc_id) {
        num_positions += j.num_positions;
        list_final.push_back(DocIDElementHeader(i.doc_id, num_positions));
        break;
      }
    }
  }
  return list_final;
}

}  // namespace hw3
