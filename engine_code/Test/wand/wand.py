#!/usr/bin/env python
#wand, assume threshold is 4,the upper bound of every term is UB

#max contribute

import time
import heapq

UB = {"t0":3.5,"t1":1,"t2":2,"t3":3,"t4":4} #upper bound of term's value
MAX_RESULT_NUM = 3 #max result number

class WAND:
    #initial index
    def __init__(self, InvertIndex, last_docid):
        self.result_list = [] #result list
        self.invert_index = InvertIndex #InvertIndex: term -> docid1, docid2, docid3 ...
        self.current_doc = 0
        self.current_invert_index = {} #posting
        self.query_terms = []
        self.threshold = -1
        self.sort_terms = []
        self.LastID = 2000000000 #big num
        self.last_docid = last_docid

    #get index list according to query term
    def __InitQuery(self, query_terms):
        self.current_doc = -1
        self.current_invert_index.clear()
        self.query_terms = query_terms
        self.sort_terms[:] = []

        for term in query_terms:
            #initial start pos from the first position of term's invert_index
            self.current_invert_index[term] = [ self.invert_index[term][0], 0 ] #[ docid, index ]

    #sort term according its current posting doc id
    def __SortTerms(self):
        if len(self.sort_terms) == 0:
            for term in self.query_terms:
                if term in self.current_invert_index:
                    doc_id = self.current_invert_index[term][0]
                    self.sort_terms.append([ int(doc_id), term ])
        self.sort_terms.sort()

    #select the first term in sorted term list
    def __PickTerm(self, pivot_index):
        return 0

    #find pivot term
    def __FindPivotTerm(self):
        score = 0
        #print "sort term ", self.sort_terms  #[docid, term]
        for i in range(0, len(self.sort_terms)):
            score = score + UB[self.sort_terms[i][1]]
            if score >= self.threshold:
                return [ self.sort_terms[i][1], i] #[term, index]

        return [ None, len(self.sort_terms)]

    #move to doc id >= docid
    def __IteratorInvertIndex(self, change_term, docid, pos):
        doc_list = self.invert_index[change_term]
        i = 0
        for i in range(pos, len(doc_list)):
            if doc_list[i] >= docid:
                pos = i
                docid = doc_list[i]
                break

        return [ docid, pos ]


    def __AdvanceTerm(self, change_index, docid ):
        change_term = self.sort_terms[change_index][1]
        pos = self.current_invert_index[change_term][1]
        (new_doc, new_pos) = self.__IteratorInvertIndex(change_term, docid, pos)

        self.current_invert_index[change_term] = [ new_doc , new_pos ]
        self.sort_terms[change_index][0] = new_doc

    def __Next(self):
        if self.last_docid == self.current_doc:
            return None

        while True:
            #sort terms by doc id
            self.__SortTerms()

            #find pivot term > threshold
            (pivot_term, pivot_index) = self.__FindPivotTerm()
            if pivot_term == None:
                #no more candidate
                return None

            pivot_doc_id = self.current_invert_index[pivot_term][0]

            if pivot_doc_id == self.LastID: #!!
                return None

            if pivot_doc_id <= self.current_doc:
                #change_index = self.__PickTerm(pivot_index)#always retrun 0
                #self.__AdvanceTerm( change_index, self.current_doc + 1 )
                for i in range(0, pivot_index + 1):
                    change_index = i
                    self.__AdvanceTerm( change_index, self.current_doc + 1 )
            else:
                first_docid = self.sort_terms[0][0]
                if pivot_doc_id == first_docid:
                    self.current_doc = pivot_doc_id
                    return self.current_doc
                else:
                    #pick all preceding term,advance to pivot
                    for i in range(0, pivot_index + 1):
                        change_index = i
                        self.__AdvanceTerm( change_index, pivot_doc_id )

    def __InsertHeap(self,doc_id,score):
        if len(self.result_list)<3:
            heapq.heappush(self.result_list, (score, doc_id))
        else:
            if score>self.result_list[0][0]: #large than mini item in heap
                heapq.heappop(self.result_list)
                heapq.heappush(self.result_list, (score, doc_id))
        return self.result_list[0][0]

    #full evaluate the doucment, get its full score, to be added
    def __FullEvaluate(self, docid):
        return 4

    def DoQuery(self, query_terms):
        self.__InitQuery(query_terms)
        while True:
            candidate_docid = self.__Next()
            if candidate_docid == None:
                break
            print "candidate_docid:" + str(candidate_docid)
            #insert candidate_docid to heap
            full_doc_score = self.__FullEvaluate(candidate_docid)
            mini_item_value = self.__InsertHeap(candidate_docid, full_doc_score)
            #update threshold
            self.threshold = mini_item_value
            print "result list ", self.result_list
        return self.result_list

if __name__ == "__main__":
    testIndex = {}
    testIndex["t0"] = [ 1, 3, 26, 2000000000]
    testIndex["t1"] = [ 1, 2, 4, 10, 100, 2000000000 ]
    testIndex["t2"] = [ 2, 3, 6, 34, 56, 2000000000 ]
    testIndex["t3"] = [ 1, 4, 5, 23, 70, 200, 2000000000 ]
    testIndex["t4"] = [ 5, 14, 78, 2000000000 ]

    last_doc_id = 100
    w = WAND(testIndex, last_doc_id)
    final_result = w.DoQuery(["t0", "t1", "t2", "t3", "t4"])
    print "final result "
    for item in final_result:
        print "doc " + str(item[1])
