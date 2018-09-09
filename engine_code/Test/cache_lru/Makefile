LruCache:main.o segment_doc_info.o profile_segment_lru_cache.o
	g++ -o LruCache main.o segment_doc_info.o profile_segment_lru_cache.o -lpthread

main.o:main.cpp
	g++ -g -c -o main.o main.cpp

segment_doc_info.o:segment_doc_info.cpp 
	g++ -g -c -o segment_doc_info.o segment_doc_info.cpp

profile_segment_lru_cache.o:profile_segment_lru_cache.cpp 
	g++ -g -c -o  profile_segment_lru_cache.o profile_segment_lru_cache.cpp

clean:
	rm LruCache main.o segment_doc_info.o profile_segment_lru_cache.o
