//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <list>
//#include <iostream>
//#include <fstream>
//#include <queue>
//using namespace std;
//#define SIZE 15000
//
//struct PacketTable {
//	unsigned int SA_ADDRESS;
//	unsigned int SA_BITMASK;
//	unsigned int DA_ADDRESS;
//	unsigned int DA_BITMASK;
//	unsigned int SP_START;
//	unsigned int SP_END;
//	unsigned int DP_START;
//	unsigned int DP_END;
//	unsigned int PT_VALUE;
//	unsigned int PT_BITMASK;
//	char SA_IPV4[33];//original SA
//	char DA_IPV4[33];
//};
//struct addressPrefix {
//	unsigned int ipv4;
//	unsigned int bitmask;
//	int originalIndex;
//	list<int> indices;
//};
//struct portRange {
//	unsigned int start;
//	unsigned int end;
//	int originalIndex;
//	list<int> indices;
//};
//struct protocol {
//	unsigned int value;
//	unsigned int bitmask;
//	int originalIndex;
//	list<int> indices;
//};
//struct treeNodeIPV4 {
//	list<treeNodeIPV4*> childList;
//	addressPrefix address;
//	int codeSpace;
//	unsigned int codeword;
//	int codemask;
//};
//struct treeNodePort {
//	list<treeNodePort*> childList;
//	portRange range;
//	int codeSpace;
//	unsigned int codeword;
//	int codemask;
//};
//struct treeNodeProtocol {
//	list<treeNodeProtocol*> childList;
//	protocol pt;
//	int codeSpace;
//	unsigned int codeword;
//	int codemask;
//};
//struct encodedRule{
//	int codeword_SA, codeword_DA, codeword_SP, codeword_DP, codeword_PT;
//	int mask_SA, mask_DA, mask_SP, mask_DP, mask_PT;
//	bool PT_flag = false; // if true, there is another rule with the same SA,DA,SP,DP and PT = *
//	int secondary_index=-1;//index of rule with PT=*;
//	bool left_right_flag = false; // false = left, true = right
//	bool redundant_flag = false;// If there is another rule with the same SA,DA,SP,DP and PT = * with higher priority
//	int unused_bits = 0;
//	unsigned long long int bv;
//	unsigned long long int bm;
//	int priority = 0;
//
//	int assigned_memory_unit;
//	list<pair<int,int> >assigned_indices;//stores <address,offset> if assigned_memory_unit > 0(normal match unit)
//};
//encodedRule table[SIZE];
//PacketTable originalTable[SIZE];
//int number_of_rules = 0;
//int ctr1 = 0;
//int sizeSA = 0;
//int sizeDA = 0;
//int sizeSP = 0, sizeDP = 0, sizePT = 0;
//int codelenSA = 0, codelenDA = 0, codelenSP = 0, codelenDP = 0, codelenPT = 0, encodedRuleLen = 0, totalEncodedRuleLen =0;
//int bram_block[32768];
//addressPrefix SA[SIZE];
//addressPrefix DA[SIZE];
//portRange SP[SIZE];
//portRange DP[SIZE];
//protocol PT[SIZE];
//bool **graph;
//
//void readFile(char* fileName);
//void ip_to_int(const char * ip,addressPrefix &prefix);
//int compareIPv4(const void* a, const void* b);
//void buildSAInclusionTree(struct treeNodeIPV4* root_SA, int& index);
//void buildDAInclusionTree(struct treeNodeIPV4* root_SA, int& index);
//bool isCompatible(unsigned int ip1, int mask1, unsigned int ip2, int mask2);
//void PrintTree(treeNodeIPV4* root);
//int assignCodeSpace(treeNodeIPV4* root);
//void removeDuplicates();
//int compareCodeSpaceIPV4(const void* a, const void* b);
//void assignCodeWord(treeNodeIPV4* t, int bits, bool flag);
//int comparePortRange(const void* a, const void* b);
//void checkOverlap();
//void buildSPInclusionTree(struct treeNodePort* root, int& index);
//void buildDPInclusionTree(struct treeNodePort* root, int& index);
//bool isCompatible_port(unsigned int start1, unsigned int end1, unsigned int start2, unsigned int end2);
//int assignCodeSpace(treeNodePort* root);
//int compareCodeSpacePort(const void* a, const void* b);
//void assignCodeWord(treeNodePort* t, int bits, bool flag);
//int compareProtocol(const void *a, const void *b);
//void buildPTInclusionTree(struct treeNodeProtocol* root, int& index);
//bool isCompatible_protocol(unsigned int value1, int mask1, unsigned int value2, int mask2);
//int assignCodeSpace(treeNodeProtocol* root);
//int compareCodeSpaceProtocol(const void* a, const void* b);
//void assignCodeWord(treeNodeProtocol* t, int bits);
//void buildPacketTable();
//void printEncodedRules();
//void printDistinctRules();
//void printPicTable(struct treeNodeIPV4 *Inclusion_SA, struct treeNodeIPV4 *Inclusion_DA, struct treeNodePort *Inclusion_SP, struct treeNodePort *Inclusion_DP, treeNodeProtocol *Inclusion_PT);
//void sortAndRemoveDuplicates();
//void assignPriority();
//bool isCompatible(unsigned long long int bv1, unsigned long long int bm1, unsigned long long int bv2, unsigned long long int bm2);
//void printDP() {
//	for (int i = 0; i < sizeDP; i++) {
//		printf("%u:%u ", DP[i].start, DP[i].end);
//	}
//	printf("\n\n");
//}
//int selected_index(int selected_bits[4], const unsigned long long int &bv, const unsigned long long int &bm);
//int selected_index_2(int selected_bits[8], const unsigned long long int&bv, const unsigned long long int &bm);//for 2-level
//int one_level_bit_selection(list<int> &indices);
//int two_level_bit_selection(list<int> &indices);
//int assign_indices(list<int> &indices, int selected_bits[8], int offset, int unit[1024][2], list<int> &wildcard);//this is for 2-level bit selection
////used to assign remaining wildcard rules to any memory location
//int assignRules();
//void buildInclusionTrees(struct treeNodeIPV4 *Inclusion_SA, struct treeNodeIPV4 *Inclusion_DA, struct treeNodePort *Inclusion_SP, struct treeNodePort *Inclusion_DP, treeNodeProtocol *Inclusion_PT);
//void bram(list<int> &indices);
//int mapRules(list<int> &indices, int selected_bits[4], int unit[1024][2]);
//char fileName[] = "10Kipc1";
//
//int main() {
//	
//	readFile(fileName);
//	sortAndRemoveDuplicates();
//	printf("number_of_rules = %d,sizeSA = %d, sizeDA = %d, sizeSP = %d, sizeDP = %d,sizePT = %d\n", number_of_rules, sizeSA, sizeDA, sizeSP, sizeDP, sizePT);
//	struct treeNodeIPV4 *Inclusion_SA = new struct treeNodeIPV4;
//	struct treeNodeIPV4 *Inclusion_DA = new struct treeNodeIPV4;
//	struct treeNodePort *Inclusion_SP = new struct treeNodePort;
//	struct treeNodePort *Inclusion_DP = new struct treeNodePort;
//	struct treeNodeProtocol *Inclusion_PT = new struct treeNodeProtocol;
//	buildInclusionTrees(Inclusion_SA, Inclusion_DA, Inclusion_SP, Inclusion_DP, Inclusion_PT);
//	totalEncodedRuleLen = encodedRuleLen + 4;
//	buildPacketTable();
//	/*freopen("output.txt", "w", stdout);
//	printEncodedRules();
//	*/
//	assignPriority();
//	FILE *temp = freopen("output_with_priority.txt", "w", stdout);
//	printEncodedRules();
//	fflush(temp);
//	freopen("CON", "w", stdout);
//	//PrintTree(Inclusion_DA);
//	/*for (int i = 0; i < number_of_rules; i++) {
//		printf("%s\n", SA_IPV4[SA[i].originalIndex]);
//	}*/
//	
//	int memory_units = assignRules();
//	printf("memory_units used = %d\n", memory_units);
//
//	return 0;
//}
//
//void sortAndRemoveDuplicates() {
//	qsort(SA, number_of_rules, sizeof(SA[0]), compareIPv4);
//	qsort(DA, number_of_rules, sizeof(DA[0]), compareIPv4);
//	qsort(SP, number_of_rules, sizeof(SP[0]), comparePortRange);
//	qsort(DP, number_of_rules, sizeof(DP[0]), comparePortRange);
//	qsort(PT, number_of_rules, sizeof(PT[0]), compareProtocol);
//	removeDuplicates();
//	int temp = number_of_rules;
//	printf("number_of_rules = %d,sizeSA = %d, sizeDA = %d, sizeSP = %d, sizeDP = %d,sizePT = %d\n", number_of_rules, sizeSA, sizeDA, sizeSP, sizeDP, sizePT);
//	checkOverlap();
//	if (number_of_rules > temp) {
//		for (int i = 0; i < number_of_rules; i++) {
//			SA[i].ipv4 = originalTable[i].SA_ADDRESS;
//			SA[i].bitmask = originalTable[i].SA_BITMASK;
//			SA[i].originalIndex = i;
//			DA[i].ipv4 = originalTable[i].DA_ADDRESS;
//			DA[i].bitmask = originalTable[i].DA_BITMASK;
//			DA[i].originalIndex = i;
//			SP[i].start = originalTable[i].SP_START;
//			SP[i].end = originalTable[i].SP_END;
//			SP[i].originalIndex = i;
//			DP[i].start = originalTable[i].DP_START;
//			DP[i].end = originalTable[i].DP_END;
//			DP[i].originalIndex = i;
//			PT[i].value = originalTable[i].PT_VALUE;
//			PT[i].bitmask = originalTable[i].PT_BITMASK;
//			PT[i].originalIndex = i;
//		}
//		qsort(SA, number_of_rules, sizeof(SA[0]), compareIPv4);
//		qsort(DA, number_of_rules, sizeof(DA[0]), compareIPv4);
//		qsort(SP, number_of_rules, sizeof(SP[0]), comparePortRange);
//		qsort(DP, number_of_rules, sizeof(DP[0]), comparePortRange);
//		qsort(PT, number_of_rules, sizeof(PT[0]), compareProtocol);
//		removeDuplicates();
//	}
//}
//
//void checkOverlap() {
//	for (int i = 0; i < sizeSP; i++) {
//		for (int j = 0; j < sizeSP; j++) {
//			if (i == j)
//				continue;
//			if (SP[j].start > SP[i].start && SP[j].start <= SP[i].end && SP[j].end>SP[i].end) {
//				int ctr_i = 0;
//				int ctr_j = 0;
//				for (int k = 0; k < number_of_rules; k++) {
//					if (originalTable[k].SP_START == SP[i].start && originalTable[k].SP_END == SP[i].end)
//						ctr_i++;
//					if (originalTable[k].SP_START == SP[j].start && originalTable[k].SP_END == SP[j].end)
//						ctr_j++;
//				}
//				if (ctr_i < ctr_j) {
//					for (int k = 0; k < number_of_rules; k++) {
//						if (originalTable[k].SP_START == SP[i].start && originalTable[k].SP_END == SP[i].end) {
//							for (int temp = number_of_rules; temp > k; temp--) {
//								originalTable[temp] = originalTable[temp - 1];
//							}
//							originalTable[k].SP_END = SP[j].start - 1;
//							originalTable[k + 1].SP_START = SP[j].start;
//							number_of_rules++;
//						}
//					}
//					SP[sizeSP].start = SP[j].start;
//					SP[sizeSP].end = SP[i].end;
//					SP[i].end = SP[j].start - 1;
//					sizeSP++;
//					i = 0;
//					j = 0;
//				}
//				else {
//					for (int k = 0; k < number_of_rules; k++) {
//						if (originalTable[k].SP_START == SP[j].start && originalTable[j].SP_END == SP[j].end) {
//							for (int temp = number_of_rules; temp > k; temp--) {
//								originalTable[temp] = originalTable[temp - 1];
//							}
//							originalTable[k].SP_END = SP[i].end;
//							originalTable[k + 1].SP_START = SP[i].end + 1;
//							number_of_rules++;
//						}
//					}
//					SP[sizeSP].start = SP[i].end + 1;
//					SP[sizeSP].end = SP[j].end;
//					SP[j].end = SP[i].end;
//					sizeSP++;
//					i = 0;
//					j = 0;
//				}
//			}
//
//		}
//	}
//
//	for (int i = 0; i < sizeDP; i++) {
//		for (int j = 0; j < sizeDP; j++) {
//			if (i == j)
//				continue;
//			if (DP[j].start > DP[i].start && DP[j].start <= DP[i].end && DP[j].end>DP[i].end) {
//				int ctr_i = 0;
//				int ctr_j = 0;
//				for (int k = 0; k < number_of_rules; k++) {
//					if (originalTable[k].DP_START == DP[i].start && originalTable[k].DP_END == DP[i].end)
//						ctr_i++;
//					if (originalTable[k].DP_START == DP[j].start && originalTable[k].DP_END == DP[j].end)
//						ctr_j++;
//				}
//				if (ctr_i < ctr_j) {
//					for (int k = 0; k < number_of_rules; k++) {
//						if (originalTable[k].DP_START == DP[i].start && originalTable[k].DP_END == DP[i].end) {
//							for (int temp = number_of_rules; temp > k; temp--) {
//								originalTable[temp] = originalTable[temp - 1];
//							}
//							originalTable[k].DP_END = DP[j].start - 1;
//							originalTable[k + 1].DP_START = DP[j].start;
//							number_of_rules++;
//						}
//					}
//					DP[sizeSP].start = DP[j].start;
//					DP[sizeSP].end = DP[i].end;
//					DP[i].end = DP[j].start - 1;
//					sizeDP++;
//					i = 0;
//					j = 0;
//				}
//				else {
//					for (int k = 0; k < number_of_rules; k++) {
//						if (originalTable[k].DP_START == DP[j].start && originalTable[k].DP_END == DP[j].end) {
//							for (int temp = number_of_rules; temp > k; temp--) {
//								originalTable[temp] = originalTable[temp - 1];
//							}
//							originalTable[k].DP_END = DP[i].end;
//							originalTable[k + 1].DP_START = DP[i].end + 1;
//							number_of_rules++;
//						}
//					}
//					DP[sizeSP].start = DP[i].end + 1;
//					DP[sizeSP].end = DP[j].end;
//					DP[j].end = DP[i].end;
//					sizeDP++;
//					i = 0;
//					j = 0;
//				}
//			}
//
//		}
//	}
//}
//
//void buildInclusionTrees(struct treeNodeIPV4 *Inclusion_SA, struct treeNodeIPV4 *Inclusion_DA, struct treeNodePort *Inclusion_SP, struct treeNodePort *Inclusion_DP, treeNodeProtocol *Inclusion_PT) {
//	Inclusion_SA[0].address = SA[0];
//	Inclusion_DA[0].address = DA[0];
//	int index = 1;
//	buildSAInclusionTree(Inclusion_SA, index);
//	index = 1;
//	buildDAInclusionTree(Inclusion_DA, index);
//	int total_codeSpaceSA = assignCodeSpace(Inclusion_SA);
//	int total_codeSpaceDA = assignCodeSpace(Inclusion_DA);
//	codelenSA = log(total_codeSpaceSA) / log(2);
//	codelenDA = log(total_codeSpaceDA) / log(2);
//	printf("total codelenSA = %ld \ttotal codelenDA = %ld\n", codelenSA, codelenDA);
//
//	Inclusion_SA[0].codeword = 0;
//	Inclusion_SA[0].codemask = 0;
//	Inclusion_DA[0].codeword = 0;
//	Inclusion_DA[0].codemask = 0;
//	assignCodeWord(Inclusion_SA, codelenSA, true);
//	assignCodeWord(Inclusion_DA, codelenDA, false);
//
//
//	Inclusion_SP[0].range = SP[0];
//	Inclusion_DP[0].range = DP[0];
//	Inclusion_SP[0].codeword = 0;
//	Inclusion_SP[0].codemask = 0;
//	Inclusion_DP->codeword = 0;
//	Inclusion_DP->codemask = 0;
//	index = 1;
//	buildSPInclusionTree(Inclusion_SP, index);
//	index = 1;
//	buildDPInclusionTree(Inclusion_DP, index);
//
//	int total_codeSpaceSP = assignCodeSpace(Inclusion_SP);
//	int total_codeSpaceDP = assignCodeSpace(Inclusion_DP);
//	codelenSP = log(total_codeSpaceSP) / log(2);
//	codelenDP = log(total_codeSpaceDP) / log(2);
//	assignCodeWord(Inclusion_SP, codelenSP, true);
//	assignCodeWord(Inclusion_DP, codelenDP, false);
//	printf("total codelenSP = %ld \ttotal codelenDP = %ld\n", codelenSP, codelenDP);
//
//
//	Inclusion_PT[0].pt = PT[0];
//	Inclusion_PT[0].codeword = 0;
//	Inclusion_PT[0].codemask = 0;
//	index = 1;
//	buildPTInclusionTree(Inclusion_PT, index);
//	int total_codespacePT = assignCodeSpace(Inclusion_PT);
//	codelenPT = log(total_codespacePT) / log(2);
//	assignCodeWord(Inclusion_PT, codelenPT);
//	printf("total codelenPT = %d\n", codelenPT);
//	encodedRuleLen = codelenDA + codelenDP + codelenPT + codelenSA + codelenSP;
//	printf("encodedruleLen = %d\n", encodedRuleLen);
//	printPicTable(Inclusion_SA, Inclusion_DA, Inclusion_SP, Inclusion_DP, Inclusion_PT);
//}
//
//int assignCodeSpace(treeNodeIPV4* root) {
//	if (root->childList.empty()) {
//		root->codeSpace = 1;
//		return 1;
//	}
//	int sum = 1;
//	for (list<treeNodeIPV4*>::iterator it = root->childList.begin(); it != root->childList.end(); it++) {
//		sum += assignCodeSpace(*it);
//	}
//	int i = 2;
//	for (i = 2; i < sum; i *= 2);
//	root->codeSpace = i;
//	return i;
//}
//
//int assignCodeSpace(treeNodePort* root) {
//	if (root->childList.empty()) {
//		root->codeSpace = 1;
//		return 1;
//	}
//	int sum = 1;
//	for (list<treeNodePort*>::iterator it = root->childList.begin(); it != root->childList.end(); it++) {
//		sum += assignCodeSpace(*it);
//	}
//	unsigned int i = 2;
//	for (i = 2; i < sum; i *= 2);
//	root->codeSpace = i;
//	return i;
//}
//
//int assignCodeSpace(treeNodeProtocol* root) {
//	if (root->childList.empty()) {
//		root->codeSpace = 1;
//		return 1;
//	}
//	int sum = 1;
//	for (list<treeNodeProtocol*>::iterator it = root->childList.begin(); it != root->childList.end(); it++) {
//		sum += assignCodeSpace(*it);
//	}
//	unsigned int i = 2;
//	for (i = 2; i < sum; i *= 2);
//	root->codeSpace = i;
//	return i;
//}
//
//void assignCodeWord(treeNodeIPV4* t, int bits, bool flag) {//if flag refers to SA otherwise DA
//	int availableCodeSpace = t->codeSpace;
//	treeNodeIPV4** temp = new treeNodeIPV4*[t->childList.size()];
//	int i = 0;
//	if (flag) {
//		table[t->address.originalIndex].codeword_SA = t->codeword;
//		table[t->address.originalIndex].mask_SA = t->codemask;
//		for (list<int>::iterator it = t->address.indices.begin(); it != t->address.indices.end(); it++) {
//			table[*it].codeword_SA = t->codeword;
//			table[*it].mask_SA = t->codemask;
//		}
//	}
//	else {
//		table[t->address.originalIndex].codeword_DA = t->codeword;
//		table[t->address.originalIndex].mask_DA = t->codemask;
//		for (list<int>::iterator it = t->address.indices.begin(); it != t->address.indices.end(); it++) {
//			table[*it].codeword_DA = t->codeword;
//			table[*it].mask_DA = t->codemask;
//		}
//	}
//	for (list<treeNodeIPV4*>::iterator it = t->childList.begin(); it != t->childList.end(); it++) {
//		temp[i++] = (*it);
//	}
//
//	qsort(temp, t->childList.size(), sizeof(treeNodeIPV4*), compareCodeSpaceIPV4);
//	for (i = 0; i < t->childList.size(); i++) {
//		int x = (temp[i])->codeSpace;
//		temp[i]->codeword = t->codeword + (availableCodeSpace - x);
//		temp[i]->codemask = bits - (log(temp[i]->codeSpace) / log(2));
//		availableCodeSpace -= x;
//		assignCodeWord((temp[i]), bits, flag);
//	}
//}
//
//void assignCodeWord(treeNodePort* t, int bits, bool flag) {
//	int availableCodeSpace = t->codeSpace;
//	treeNodePort** temp = new treeNodePort*[t->childList.size()];
//	int i = 0;
//	if (flag) {
//		table[t->range.originalIndex].codeword_SP = t->codeword;
//		table[t->range.originalIndex].mask_SP = t->codemask;
//		for (list<int>::iterator it = t->range.indices.begin(); it != t->range.indices.end(); it++) {
//			table[*it].codeword_SP = t->codeword;
//			table[*it].mask_SP = t->codemask;
//		}
//	}
//	else {
//		table[t->range.originalIndex].codeword_DP = t->codeword;
//		table[t->range.originalIndex].mask_DP = t->codemask;
//		for (list<int>::iterator it = t->range.indices.begin(); it != t->range.indices.end(); it++) {
//			table[*it].codeword_DP = t->codeword;
//			table[*it].mask_DP = t->codemask;
//		}
//	}
//	for (list<treeNodePort*>::iterator it = t->childList.begin(); it != t->childList.end(); it++) {
//		temp[i++] = (*it);
//	}
//	qsort(temp, t->childList.size(), sizeof(treeNodePort*), compareCodeSpacePort);
//	for (i = 0; i < t->childList.size(); i++) {
//		int x = (temp[i])->codeSpace;
//		temp[i]->codeword = t->codeword + (availableCodeSpace - x);
//		temp[i]->codemask = bits - (log(temp[i]->codeSpace) / log(2));
//		availableCodeSpace -= x;
//		assignCodeWord((temp[i]), bits, flag);
//	}
//}
//
//void assignCodeWord(treeNodeProtocol* t, int bits) {
//	int availableCodeSpace = t->codeSpace;
//	treeNodeProtocol** temp = new treeNodeProtocol*[t->childList.size()];
//	int i = 0;
//	for (list<treeNodeProtocol*>::iterator it = t->childList.begin(); it != t->childList.end(); it++) {
//		temp[i++] = (*it);
//	}
//	table[t->pt.originalIndex].codeword_PT = t->codeword;
//	table[t->pt.originalIndex].mask_PT = t->codemask;
//	for (list<int>::iterator it = t->pt.indices.begin(); it != t->pt.indices.end(); it++) {
//		table[*it].codeword_PT = t->codeword;
//		table[*it].mask_PT = t->codemask;
//	}
//	qsort(temp, t->childList.size(), sizeof(treeNodeProtocol*), compareCodeSpaceIPV4);
//	for (i = 0; i < t->childList.size(); i++) {
//		int x = (temp[i])->codeSpace;
//		temp[i]->codeword = t->codeword + (availableCodeSpace - x);
//		temp[i]->codemask = bits - (log(temp[i]->codeSpace) / log(2));
//		availableCodeSpace -= x;
//		assignCodeWord((temp[i]), bits);
//	}
//}
//
//void PrintTree(treeNodeIPV4* root) {
//	printf(".\t %x/%d\t\t", root->codeword, root->codemask);
//	printf("%s\n", originalTable[root->address.originalIndex].DA_IPV4);
//	for (list<treeNodeIPV4*>::iterator it = root->childList.begin(); it != root->childList.end(); it++) {
//		PrintTree(*it);
//	}
//}
//
//void buildSAInclusionTree(struct treeNodeIPV4* root_SA, int& index) {
//	while (index<sizeSA && isCompatible(root_SA->address.ipv4, root_SA->address.bitmask, SA[index].ipv4, SA[index].bitmask)){
//		treeNodeIPV4* child = new treeNodeIPV4;
//		child->address = SA[index];
//		root_SA->childList.push_back(child);
//		buildSAInclusionTree(child, ++index);
//	}
//}
//
//void buildDAInclusionTree(struct treeNodeIPV4* root_DA, int& index) {
//	while (index<sizeDA && isCompatible(root_DA->address.ipv4,root_DA->address.bitmask,DA[index].ipv4,DA[index].bitmask)) {
//		treeNodeIPV4* child = new treeNodeIPV4;
//		child->address = DA[index];
//		root_DA->childList.push_back(child);
//		buildDAInclusionTree(child, ++index);
//	}
//}
//
//void buildSPInclusionTree(struct treeNodePort* root, int& index) {
//	while (index < sizeSP && isCompatible_port(root->range.start, root->range.end, SP[index].start, SP[index].end)) {
//		treeNodePort* child = new treeNodePort;
//		child->range = SP[index];
//		root->childList.push_back(child);
//		buildSPInclusionTree(child, ++index);
//	}
//}
//
//void buildDPInclusionTree(struct treeNodePort* root, int& index) {
//	while (index < sizeDP && isCompatible_port(root->range.start, root->range.end, DP[index].start, DP[index].end)) {
//		treeNodePort* child = new treeNodePort;
//		child->range =DP[index];
//		root->childList.push_back(child);
//		buildDPInclusionTree(child, ++index);
//	}
//}
//
//void buildPTInclusionTree(struct treeNodeProtocol* root, int& index) {
//	while (index < sizePT && isCompatible_protocol(root->pt.value, root->pt.bitmask, PT[index].value, PT[index].bitmask)) {
//		treeNodeProtocol* child = new treeNodeProtocol;
//		child->pt = PT[index];
//		root->childList.push_back(child);
//		buildPTInclusionTree(child, ++index);
//	}
//}
//
//bool isCompatible(unsigned int ip1, int mask1, unsigned int ip2, int mask2) {
//	//returns true if ip2, is compatible with ip1.
//	for (int i = 0; i < 32; i++) {
//		if (i >= mask1)
//			return true;
//		if (i >= mask2)
//			return false;
//		if ( ((ip1 >> (31 - i)) & 1) != ((ip2 >> (31 - i)) & 1) ) {
//			return false;
//		}
//	}
//	return true;
//}
//
//bool isCompatible_protocol(unsigned int value1, int mask1, unsigned int value2, int mask2) {
//	//returns true if ip2, is compatible with ip1.
//	for (int i = 0; i < 8; i++) {
//		if (i >= mask1)
//			return true;
//		if (i >= mask2)
//			return false;
//		if (((value1 >> (7 - i)) & 1) != ((value2 >> (7 - i)) & 1)) {
//			return false;
//		}
//	}
//	return true;
//}
//
//bool isCompatible_port(unsigned int start1, unsigned int end1, unsigned int start2, unsigned int end2) {
//	//returns true is range 2 is a subrange of 1
//	if (start2 >= start1 && start2 <= end1 && end2 >= start1 && end2 <= end1)
//		return true;
//	return false;
//}
//
//int compareCodeSpaceIPV4(const void* a, const void* b) {
//	treeNodeIPV4** t1 = (treeNodeIPV4**)a;
//	treeNodeIPV4** t2 = (treeNodeIPV4**)b;
//	return (*t2)->codeSpace - (*t1)->codeSpace;
//}
//
//int compareCodeSpacePort(const void* a, const void* b) {
//	treeNodePort** t1 = (treeNodePort**)a;
//	treeNodePort** t2 = (treeNodePort**)b;
//	return (*t2)->codeSpace - (*t1)->codeSpace;
//}
//
//int compareCodeSpaceProtocol(const void* a, const void* b) {
//	treeNodeProtocol** t1 = (treeNodeProtocol**)a;
//	treeNodeProtocol** t2 = (treeNodeProtocol**)b;
//	return (*t2)->codeSpace - (*t1)->codeSpace;
//}
//
//void removeDuplicates() {
//	int j = 0;
//	int ctr = 0;
//	for (int i = 0; i < number_of_rules - 1; i++) {
//		if (SA[i].bitmask != SA[i + 1].bitmask) {
//			SA[j].indices = list<int>();
//			for (int z = ctr; z < i; z++) {
//				SA[j].indices.push_back(SA[z].originalIndex);
//			}
//			SA[j].bitmask = SA[i].bitmask;
//			SA[j].ipv4 = SA[i].ipv4;
//			SA[j].originalIndex = SA[i].originalIndex;
//			j++;
//			ctr = i + 1;
//		}
//		else {
//			for (int k = 0; k < 32; k++) {
//				if (((SA[i].ipv4 >> (31 - k)) & 1) != ((SA[i + 1].ipv4 >> (31 - k)) & 1)) {
//					SA[j].indices = list<int>();
//					for (int z = ctr; z < i; z++) {
//						SA[j].indices.push_back(SA[z].originalIndex);
//					}
//					SA[j].bitmask = SA[i].bitmask;
//					SA[j].ipv4 = SA[i].ipv4;
//					SA[j].originalIndex = SA[i].originalIndex;
//					j++;
//					ctr = i + 1;
//					break;
//				}
//			}
//		}
//	}
//	SA[j].indices = list<int>();
//	for (int z = ctr; z < number_of_rules - 1; z++) {
//		SA[j].indices.push_back(SA[z].originalIndex);
//	}
//	SA[j].bitmask = SA[number_of_rules-1].bitmask;
//	SA[j].ipv4 = SA[number_of_rules-1].ipv4;
//	SA[j].originalIndex = SA[number_of_rules-1].originalIndex;
//	sizeSA = ++j;
//
//	j = 0;
//	ctr = 0;
//	for (int i = 0; i < number_of_rules - 1; i++) {
//		if (DA[i].bitmask != DA[i + 1].bitmask) {
//			DA[j].indices = list<int>();
//			for (int z = ctr; z < i; z++) {
//				DA[j].indices.push_back(DA[z].originalIndex);
//			}
//			DA[j].bitmask = DA[i].bitmask;
//			DA[j].ipv4 = DA[i].ipv4;
//			DA[j].originalIndex = DA[i].originalIndex;
//			j++;
//			ctr = i + 1;
//		}
//		else {
//			for (int k = 0; k < 32; k++) {
//				if (((DA[i].ipv4 >> (31 - k)) & 1) != ((DA[i + 1].ipv4 >> (31 - k)) & 1)) {
//					DA[j].indices = list<int>();
//					for (int z = ctr; z < i; z++) {
//						DA[j].indices.push_back(DA[z].originalIndex);
//					}
//					DA[j].bitmask = DA[i].bitmask;
//					DA[j].ipv4 = DA[i].ipv4;
//					DA[j].originalIndex = DA[i].originalIndex;
//					j++;
//					ctr = i + 1;
//					break;
//				}
//			}
//		}
//	}
//	DA[j].indices = list<int>();
//	for (int z = ctr; z < number_of_rules - 1; z++) {
//		DA[j].indices.push_back(DA[z].originalIndex);
//	}
//	DA[j].bitmask = DA[number_of_rules-1].bitmask;
//	DA[j].ipv4 = DA[number_of_rules-1].ipv4;
//	DA[j].originalIndex = DA[number_of_rules-1].originalIndex;
//	j++;
//	sizeDA = j;
//
//	j = 0;
//	ctr = 0;
//	for (int i = 0; i < number_of_rules - 1; i++) {
//		if (!(SP[i].start == SP[i + 1].start && SP[i].end == SP[i + 1].end)) {
//			SP[j].start = SP[i].start;
//			SP[j].end = SP[i].end;
//			SP[j].originalIndex = SP[i].originalIndex;
//			SP[j].indices = list<int>();
//			for (int z = ctr; z < i; z++) {
//				SP[j].indices.push_back(SP[z].originalIndex);
//			}
//			ctr = i + 1;
//			j++;
//		}
//	}
//	SP[j].start = SP[number_of_rules-1].start;
//	SP[j].end = SP[number_of_rules - 1].end;
//	SP[j].originalIndex = SP[number_of_rules - 1].originalIndex;
//	SP[j].indices = list<int>();
//	for (int z = ctr; z < number_of_rules-1; z++) {
//		SP[j].indices.push_back(SP[z].originalIndex);
//	}
//	j++;
//	sizeSP = j;
//
//	j = 0;
//	ctr = 0;
//	for (int i = 0; i < number_of_rules - 1; i++) {
//		if (!(DP[i].start == DP[i + 1].start && DP[i].end == DP[i + 1].end)) {
//			DP[j].start = DP[i].start;
//			DP[j].end = DP[i].end;
//			DP[j].originalIndex = DP[i].originalIndex;
//			DP[j].indices = list<int>();
//			for (int z = ctr; z < i; z++) {
//				DP[j].indices.push_back(DP[z].originalIndex);
//			}
//			ctr = i + 1;
//			j++;
//		}
//	}
//	DP[j].start = DP[number_of_rules - 1].start;
//	DP[j].end = DP[number_of_rules - 1].end;
//	DP[j].originalIndex = DP[number_of_rules - 1].originalIndex;
//	DP[j].indices = list<int>();
//	for (int z = ctr; z < number_of_rules - 1; z++) {
//		DP[j].indices.push_back(DP[z].originalIndex);
//	}
//	j++;
//	sizeDP = j;
//
//	j = 0;
//	ctr = 0;
//	for (int i = 0; i < number_of_rules - 1; i++) {
//		if (PT[i].bitmask != PT[i + 1].bitmask) {
//			PT[j].indices = list<int>();
//			for (int z = ctr; z < i; z++) {
//				PT[j].indices.push_back(PT[z].originalIndex);
//			}
//			PT[j].bitmask = PT[i].bitmask;
//			PT[j].value = PT[i].value;
//			PT[j].originalIndex = PT[i].originalIndex;
//			j++;
//			ctr = i + 1;
//		}
//		else {
//			for (int k = 0; k < 8; k++) {
//				if (((PT[i].value >> (7 - k)) & 1) != ((PT[i + 1].value >> (7 - k)) & 1)) {
//					PT[j].indices = list<int>();
//					for (int z = ctr; z < i; z++) {
//						PT[j].indices.push_back(PT[z].originalIndex);
//					}
//					PT[j].bitmask = PT[i].bitmask;
//					PT[j].value = PT[i].value;
//					PT[j].originalIndex = PT[i].originalIndex;
//					j++;
//					ctr = i + 1;
//					break;
//				}
//			}
//		}
//	}
//	PT[j].indices = list<int>();
//	for (int z = ctr; z < number_of_rules - 1; z++) {
//		PT[j].indices.push_back(PT[z].originalIndex);
//	}
//	PT[j].bitmask = PT[number_of_rules - 1].bitmask;
//	PT[j].value = PT[number_of_rules - 1].value;
//	PT[j].originalIndex = PT[number_of_rules - 1].originalIndex;
//	sizePT = ++j;
//}
//
//void readFile(char* fileName) {
//	char temp[50];
//	strcpy(temp, fileName);
//	FILE * fp = fopen(strcat(temp,"_norm"), "r");
//	if (fp == NULL) {
//		printf("Error! opening file\n");
//		exit(0);
//	}
//	char line[50];
//	int i = 0;
//	while (fscanf(fp, "%s\n", line) != EOF) {
//		ip_to_int(line + 1, SA[i]);//start from the character after the @ symbol
//		originalTable[i].SA_ADDRESS = SA[i].ipv4;
//		originalTable[i].SA_BITMASK = SA[i].bitmask;
//		memcpy(originalTable[i].SA_IPV4, line + 1, sizeof(char) * 32);
//		originalTable[i].SA_IPV4[32] = '\0';
//		SA[i].originalIndex = i;
//
//		fscanf(fp, "%s\n", line);
//		memcpy(originalTable[i].DA_IPV4, line, sizeof(char) * 32);
//		ip_to_int(line, DA[i]);
//		originalTable[i].DA_ADDRESS = DA[i].ipv4;
//		originalTable[i].DA_BITMASK = DA[i].bitmask;
//		DA[i].originalIndex = i;
//		originalTable[i].DA_IPV4[32] = '\0';
//		
//		fscanf(fp, "%d\n", &originalTable[i].SP_START);
//		SP[i].start = originalTable[i].SP_START;
//		SP[i].originalIndex = i;
//		
//		fscanf(fp, ": %d\n", &originalTable[i].SP_END);
//		SP[i].end = originalTable[i].SP_END;
//		
//		fscanf(fp, "%d\n", &originalTable[i].DP_START);
//		DP[i].start = originalTable[i].DP_START;
//		fscanf(fp, ": %d\n", &originalTable[i].DP_END);
//		DP[i].end = originalTable[i].DP_END;
//		DP[i].originalIndex = i;
//		
//		fscanf(fp, "0x%x/0x%x\n", &originalTable[i].PT_VALUE, &originalTable[i].PT_BITMASK);
//		PT[i].value = originalTable[i].PT_VALUE;
//		PT[i].bitmask = originalTable[i].PT_BITMASK;
//		PT[i].originalIndex = i;
//		fscanf(fp, "%s\n", line);//ignore protocol flags
//		i++;
//	}
//	number_of_rules = i;
//}
//
//void ip_to_int(const char * ip,addressPrefix &prefix){
//	unsigned v = 0;
//	int i; // counter to keep track of the number of bytes that have been processed
//
//	const char * start;//pointer to start read each byte
//
//	start = ip;
//	for (i = 0; i < 4; i++) {
//		/* The digit being processed. */
//		char c;
//		/* The value of this byte. */
//		int n = 0;
//		while (1) {
//			c = *start;
//			start++;
//			if (c >= '0' && c <= '9') {
//				n *= 10;
//				n += c - '0';
//			}
//			/* We insist on stopping at "." if we are still parsing
//			the first, second, or third numbers. If we have reached
//			the end of the numbers, we will allow any character. */
//			else if ((i < 3 && c == '.') || i == 3) {
//				break;
//			}
//			else {
//				prefix.ipv4 = 0;
//			}
//		}
//		if (n >= 256) {
//			prefix.ipv4 = 0;
//		}
//		v *= 256;
//		v += n;
//	}
//	prefix.ipv4 = v;
//	unsigned int subnet_mask = 0;
//	while (*start != '\0') {
//		subnet_mask = (subnet_mask * 10) + (*start - '0');
//		start++;
//	}
//	prefix.bitmask = subnet_mask;
//}
//
//int compareIPv4(const void* a, const void* b) {
//	addressPrefix* p1 = (addressPrefix*)a;
//	addressPrefix* p2 = (addressPrefix*)b;
//	for (int i = 0; i < 32; i++) {
//		if (i >= p1->bitmask) {
//			return -1;
//		}
//		if (i >= p2->bitmask) {
//			return 1;
//		}
//		if ( ((p1->ipv4 >> (31 - i))&1) != ((p2->ipv4 >> (31 - i)) & 1)) {
//			if (((p1->ipv4 >> (31 - i)) & 1) == 1)
//				return 1;
//			else return -1;
//		}
//	}
//	return 0;
//}
//
//int comparePortRange(const void* a, const void* b) {
//	portRange* p1 = (portRange*)a;
//	portRange* p2 = (portRange*)b;
//	int s1 = p1->start;
//	int s2 = p2->start;
//	if (s1 == s2) {
//		int r1 = p1->end - p1->start;
//		int r2 = p2->end - p2->start;
//		return r2 - r1;
//	}
//	return s1 - s2;
//
//}
//
//int compareProtocol(const void* a, const void* b) {
//	protocol* p1 = (protocol*)a;
//	protocol* p2 = (protocol*)b;
//	for (int i = 0; i < 8; i++) {
//		if (i >= p1->bitmask) {
//			return -1;
//		}
//		if (i >= p2->bitmask) {
//			return 1;
//		}
//		if (((p1->value >> (7 - i)) & 1) != ((p2->value >> (7 - i)) & 1)) {
//			if (((p1->value >> (7 - i)) & 1) == 1)
//				return 1;
//			else return -1;
//		}
//	}
//	return 0;
//}
//
//void buildPacketTable() {
//	for (int i = 0; i < number_of_rules - 1; i++) {// removing duplicate rules
//		for (int j = i + 1; j < number_of_rules; j++) {
//			if (table[i].codeword_SA == table[j].codeword_SA && table[i].codeword_DA == table[j].codeword_DA
//				&& table[i].codeword_SP == table[j].codeword_SP && table[i].codeword_DP == table[j].codeword_DP
//				&& table[i].mask_SA == table[j].mask_SA && table[i].mask_DA == table[j].mask_DA
//				&& table[i].mask_SP == table[j].mask_SP && table[i].mask_DP == table[j].mask_DP
//				&& table[i].mask_PT == table[j].mask_PT && table[i].codeword_PT == table[j].codeword_PT) {
//				for (int k = j + 1; k < number_of_rules; k++) {
//					table[k - 1] = table[k];
//					originalTable[k - 1] = originalTable[k];
//				}
//				number_of_rules--;
//			}
//		}
//	}
//	printf("distinct_rules = %d", number_of_rules);
//	printDistinctRules();
//	int shift_value = 0;
//	for (int i = 0; i < number_of_rules; i++) {
//		shift_value = 0;
//		for (int j = 1; j <= codelenSA; j++) {
//			if (j <= table[i].mask_SA) {//this means that this bit is a value and not a don't care
//				if (((table[i].codeword_SA >> (codelenSA - j)) & 1) == 1)
//					table[i].bv |= (1ULL << (encodedRuleLen - shift_value - j));//bit set
//				else
//					table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));//bit clear
//				table[i].bm |= (1ULL << (encodedRuleLen - shift_value - j));
//			}
//			else {
//				table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//				table[i].bm &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//			}
//		}
//		shift_value += codelenSA;
//		for (int j = 1; j <= codelenDA; j++) {
//			if (j <= table[i].mask_DA) {//this means that this bit is a value and not a don't care
//				if (((table[i].codeword_DA >> (codelenDA - j)) & 1) == 1)
//					table[i].bv |= (1ULL << (encodedRuleLen - shift_value - j));//bit set
//				else
//					table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));//bit clear
//				table[i].bm |= (1ULL << (encodedRuleLen - shift_value - j));
//			}
//			else {
//				table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//				table[i].bm &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//			}
//		}
//		shift_value += codelenDA;
//		for (int j = 1; j <= codelenSP; j++) {
//			if (j <= table[i].mask_SP) {//this means that this bit is a value and not a don't care
//				if (((table[i].codeword_SP >> (codelenSP - j)) & 1) == 1)
//					table[i].bv |= (1ULL << (encodedRuleLen - shift_value - j));//bit set
//				else
//					table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));//bit clear
//				table[i].bm |= (1ULL << (encodedRuleLen - shift_value - j));
//			}
//			else {
//				table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//				table[i].bm &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//			}
//		}
//		shift_value += codelenSP;
//		for (int j = 1; j <= codelenDP; j++) {
//			if (j <= table[i].mask_DP) {//this means that this bit is a value and not a don't care
//				if (((table[i].codeword_DP >> (codelenDP - j)) & 1) == 1)
//					table[i].bv |= (1ULL << (encodedRuleLen - shift_value - j));//bit set
//				else
//					table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));//bit clear
//				table[i].bm |= (1ULL << (encodedRuleLen - shift_value - j));
//			}
//			else {
//				table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//				table[i].bm &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//			}
//		}
//		shift_value += codelenDP;
//		for (int j = 1; j <= codelenPT; j++) {
//			if (j <= table[i].mask_PT) {//this means that this bit is a value and not a don't care
//				if (((table[i].codeword_PT >> (codelenPT - j)) & 1) == 1)
//					table[i].bv |= (1ULL << (encodedRuleLen - shift_value - j));//bit set
//				else
//					table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));//bit clear
//				table[i].bm |= (1ULL << (encodedRuleLen - shift_value - j));
//			}
//			else {
//				table[i].bv &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//				table[i].bm &= (~(1ULL << (encodedRuleLen - shift_value - j)));
//			}
//		}
//		table[i].unused_bits = (codelenSA - table[i].mask_SA) + (codelenDA - table[i].mask_DA) + 
//			(codelenSP - table[i].mask_SP) + (codelenDP - table[i].mask_DP) + (codelenPT - table[i].mask_PT);
//	}
//}
//
//void printDistinctRules() {
//	char name[50];
//	strcpy(name, fileName);
//	FILE *temp = freopen(strcat(name,"_distinct_rules.txt"), "w", stdout);
//	for (int i = 0; i < number_of_rules; i++) {
//		printf("%d.\t%s\t%s\t%d : %d\t%d : %d\t0x%x/%x\n", (i + 1), originalTable[i].SA_IPV4, originalTable[i].DA_IPV4, 
//			originalTable[i].SP_START, originalTable[i].SP_END, originalTable[i].DP_START, originalTable[i].DP_END, 
//			originalTable[i].PT_VALUE, originalTable[i].PT_BITMASK);
//	}
//	fflush(temp);
//	freopen("CON", "w", stdout);
//}
//
//void printPicTable(struct treeNodeIPV4 *Inclusion_SA, struct treeNodeIPV4 *Inclusion_DA, struct treeNodePort *Inclusion_SP, struct treeNodePort *Inclusion_DP, treeNodeProtocol *Inclusion_PT) {
//	char name[50];
//	strcpy(name, fileName);
//	FILE *temp = freopen(strcat(name, "_PIC_tables.txt"), "w", stdout);
//	printf("sizeSA = %d, sizeDA = %d\nsizeSP = %d, sizeDP = %d\nsizePT = %d\n\n", sizeSA, sizeDA, sizeSP, sizeDP, sizePT);
//	printf("codelenSA = %d, codelenDA = %d\ncodelenSP = %d, codelenDP = %d\ncodelenPT = %d\n\n", codelenSA, codelenDA, codelenSP, codelenDP, codelenPT);
//	printf("encodedRuleLen = %d\n\n", encodedRuleLen);
//
//	printf("tableSA:\n");
//	int ctr = 0;
//	queue<treeNodeIPV4*> ip;
//	ip.push(Inclusion_SA);
//	while (!ip.empty()) {
//		printf("%4d : %08x/%d\t, %s\t: %08x/%d\n",ctr++,ip.front()->address.ipv4, ip.front()->address.bitmask,
//			originalTable[ip.front()->address.originalIndex].SA_IPV4,ip.front()->codeword,ip.front()->codemask);
//		for (list<treeNodeIPV4*>::iterator it = ip.front()->childList.begin(); it != ip.front()->childList.end(); it++) {
//			ip.push(*it);
//		}
//		ip.pop();
//	}
//
//	printf("\ntableDA:\n");
//	ip.push(Inclusion_DA);
//	ctr = 0;
//	while (!ip.empty()) {
//		printf("%4d : %08x/%d\t, %s\t: %08x/%d\n", ctr++, ip.front()->address.ipv4, ip.front()->address.bitmask,
//			originalTable[ip.front()->address.originalIndex].DA_IPV4, ip.front()->codeword, ip.front()->codemask);
//		for (list<treeNodeIPV4*>::iterator it = ip.front()->childList.begin(); it != ip.front()->childList.end(); it++) {
//			ip.push(*it);
//		}
//		ip.pop();
//	}
//
//	printf("\ntableSP:\n");
//	ctr = 0;
//	queue<treeNodePort*> port;
//	port.push(Inclusion_SP);
//	while (!port.empty()) {
//		printf("%4d : %d : %d\t: %08x/%d\n", ctr++, port.front()->range.start, port.front()->range.end, 
//			port.front()->codeword, port.front()->codemask);
//		for (list<treeNodePort*>::iterator it = port.front()->childList.begin(); it != port.front()->childList.end(); it++) {
//			port.push(*it);
//		}
//		port.pop();
//	}
//
//	printf("\ntableDP:\n");
//	ctr = 0;
//	port.push(Inclusion_DP);
//	while (!port.empty()) {
//		printf("%4d : %d : %d\t: %08x/%d\n", ctr++, port.front()->range.start, port.front()->range.end,
//			port.front()->codeword, port.front()->codemask);
//		for (list<treeNodePort*>::iterator it = port.front()->childList.begin(); it != port.front()->childList.end(); it++) {
//			port.push(*it);
//		}
//		port.pop();
//	}
//
//	printf("\ntablePT:\n");
//	ctr = 0;
//	queue<treeNodeProtocol*> pt;
//	pt.push(Inclusion_PT);
//	while (!pt.empty()) {
//		printf("%4d : %d : %d\t: %08x/%d\n", ctr++, pt.front()->pt.value, pt.front()->pt.bitmask,
//			pt.front()->codeword, pt.front()->codemask);
//		for (list<treeNodeProtocol*>::iterator it = pt.front()->childList.begin(); it != pt.front()->childList.end(); it++) {
//			pt.push(*it);
//		}
//		pt.pop();
//	}
//	fflush(temp);
//	freopen("CON", "w", stdout);
//}
//
//void printEncodedRules() {
//	for (int i = 0; i < number_of_rules; i++) {
//		int j;
//		for (j = 1; j <= encodedRuleLen; j++) {
//			printf("%llu", table[i].bv >> (encodedRuleLen - j) & 1);
//		}
//		printf("\t%d\n",table[i].priority);
//		for (j = 1; j <= encodedRuleLen; j++) {
//			printf("%llu", table[i].bm >> (encodedRuleLen - j) & 1);
//		}
//		printf("\n\n");
//	}
//}
//
//void assignPriority() {
//	graph = new bool*[number_of_rules];
//	int max_value = 0;
//	for (int i = 0; i < number_of_rules; i++){
//		graph[i] = new bool[number_of_rules];
//		memset(graph[i], 0, sizeof(bool)*number_of_rules);
//	}
//	for (int i = number_of_rules - 1 ; i >= 0; i--) {
//		for (int j = i-1; j >= 0; j--) {
//			if (isCompatible(table[i].bv,table[i].bm,table[j].bv,table[j].bm)) {//if j is compatible with i
//				graph[i][j] = 1;
//				graph[j][i] = 0;
//			}
//		}
//	}
//	queue<pair<int,int> > q;
//	q.push(make_pair(number_of_rules - 1,0));
//	while (!q.empty()) {
//		int index = q.front().first;
//		int value = q.front().second;
//		max_value = value > max_value ? value : max_value;
//		q.pop();
//		for (int i = 0; i < number_of_rules - 1; i++) {
//			if (graph[index][i] == 1){
//				int temp = value + 1;
//				table[i].priority = temp;
//				q.push(make_pair(i, temp));
//			}
//		}
//	}
//	printf("\nmax_priority = %d\n", max_value);
//	int shadowed_rules_ctr = 0;
//	int case1_rules = 0;
//	list<pair<int,int >> case1_indices;// first index is the rule with PT=* and second is the rule with PT=value
//	//Removing rules with same SA,DA,SP,DP values and one rule with a PT value and the other with a wildcard.
//	//Case 1: rule with PT = value ---> rule with PT = *
//	//rule with PT = value--->other rule--->rule with PT = *
//	for (int i = 0; i < number_of_rules; i++) {	 
//		if (table[i].mask_PT == 0) {//wildcard protocol
//			bool flag = false;
//			for (int j = 0; j < number_of_rules; j++) {
//				if (i == j)
//					continue;
//				if (table[i].codeword_SA == table[j].codeword_SA && table[i].codeword_DA == table[j].codeword_DA
//					&& table[i].codeword_SP == table[j].codeword_SP && table[i].codeword_DP == table[j].codeword_DP
//					&& table[i].mask_SA == table[j].mask_SA && table[i].mask_DA == table[j].mask_DA
//					&& table[i].mask_SP == table[j].mask_SP && table[i].mask_DP == table[j].mask_DP) {
//					queue<int> temp_queue;
//					temp_queue.push(j);
//					bool found = false;
//					while (!temp_queue.empty()) {//BFS
//						int index = temp_queue.front();
//						temp_queue.pop();
//						for (int k = 0; k < number_of_rules; k++) {
//							if (graph[index][k] == 1) {
//								if (k == i) {
//									found = true;
//									break;
//								}
//								temp_queue.push(k);
//							}
//						}
//						if (found) {
//							case1_indices.push_back(make_pair(i, j));
//							case1_rules++;
//							break;
//						}
//					}				
//				}
//			}
//		}
//	}
//
//	int case2_rules = 0;
//	list<pair<int, int >> case2_indices;// first index is the rule with PT=* and second is the rule with PT=value
//	//case 2: rule with PT = *--->rule with PT = value--->other rule
//	for (int i = 0; i < number_of_rules; i++) {
//		if (table[i].mask_PT == 0) {//wildcard protocol
//			bool flag = false;
//			for (int j = 0; j < number_of_rules; j++) {
//				if (i == j)
//					continue;
//				if (table[i].codeword_SA == table[j].codeword_SA && table[i].codeword_DA == table[j].codeword_DA
//					&& table[i].codeword_SP == table[j].codeword_SP && table[i].codeword_DP == table[j].codeword_DP
//					&& table[i].mask_SA == table[j].mask_SA && table[i].mask_DA == table[j].mask_DA
//					&& table[i].mask_SP == table[j].mask_SP && table[i].mask_DP == table[j].mask_DP) {
//					if (graph[i][j] == 1) {
//						case2_indices.push_back(make_pair(i, j));
//						case2_rules++;
//					}
//				}
//			}
//		}
//	}
//	int case3_rules = 0;
//	int case4_rules = 0;
//	list<pair<int, int >> case3_indices;// first index is the rule with PT=* and second is the rule with PT=value
//	list<pair<int, int >> case4_indices;
//	//case 3:Some other rule in between.
//	for (int i = 0; i < number_of_rules; i++) {
//		if (table[i].mask_PT == 0) {//wildcard protocol
//			bool flag = false;
//			for (int j = 0; j < number_of_rules; j++) {
//				if (i == j)
//					continue;
//				if (table[i].codeword_SA == table[j].codeword_SA && table[i].codeword_DA == table[j].codeword_DA
//					&& table[i].codeword_SP == table[j].codeword_SP && table[i].codeword_DP == table[j].codeword_DP
//					&& table[i].mask_SA == table[j].mask_SA && table[i].mask_DA == table[j].mask_DA
//					&& table[i].mask_SP == table[j].mask_SP && table[i].mask_DP == table[j].mask_DP) {
//					if (i == 9734 && j == 9716) {
//						int x = 5;
//					}
//					queue<pair<int,int> > temp_queue;//index, dist from root
//					temp_queue.push(make_pair(j, 0));
//					bool flag = true;
//					while (!temp_queue.empty() && flag) {
//						int index = temp_queue.front().first;
//						int dist = temp_queue.front().second;
//						int new_dist = dist + 1;
//						temp_queue.pop();
//						for (int k = 0; k < number_of_rules ; k++) {
//							if (graph[k][index] == 1) {
//								if (k == i) {
//									if (new_dist == 2) {
//										case3_rules++;
//										case3_indices.push_back(make_pair(i, j));
//									}
//									else if (new_dist > 2) {
//										case4_rules++;
//										case1_indices.push_back(make_pair(i, j));
//										flag = false;
//										break;
//									}
//								}
//								temp_queue.push(make_pair(k, new_dist));
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	printf("case1_rules = %d\ncase2_rules = %d\ncase3_rules = %d\ncase4_rules = %d\n", case1_rules, case2_rules, case3_rules, case4_rules);
//	int *rules = new int[number_of_rules];
//	memset(rules, 0, sizeof(int)*number_of_rules);
//	for (list<pair<int, int> >::iterator it = case4_indices.begin(); it != case4_indices.end(); it++) {
//		rules[it->second] = 1;//cannot be condensed into 1 rule
//	}
//	for (list<pair<int, int> >::iterator it = case3_indices.begin(); it != case3_indices.end(); it++) {
//		if (rules[it->second] == 0) {
//			table[it->first].PT_flag = true;
//			table[it->second].PT_flag = true;
//			table[it->second].secondary_index = it->first;//first is the rule with wildcard = *
//			rules[it->second] = 2;//priority does not need to be changed
//			rules[it->first] = 2;
//			shadowed_rules_ctr++;
//		}
//	}
//	for (list<pair<int, int> >::iterator it = case2_indices.begin(); it != case2_indices.end(); it++) {
//		if (rules[it->first] == 0 && rules[it->second] == 0) {
//			table[it->first].PT_flag = true;
//			table[it->second].PT_flag = true;
//			table[it->second].secondary_index = it->first;
//			table[it->second].priority++;
//			shadowed_rules_ctr++;
//			rules[it->first] = 3;
//			rules[it->second] = 3;
//			queue<int> temp_queue;
//			temp_queue.push(it->second);
//			while (!temp_queue.empty()) {
//				int index = temp_queue.front();
//				temp_queue.pop();
//				int new_priority = table[index].priority + 1;
//				for (int i = 0; i < number_of_rules; i++) {
//					if (graph[index][i] == 1 && new_priority > table[i].priority) {
//						table[i].priority = new_priority;
//						temp_queue.push(i);
//					}
//				}
//			}
//		}
//	}
//	for (list<pair<int, int> >::iterator it = case1_indices.begin(); it != case1_indices.end(); it++) {
//		int index = it->second;
//		table[index].redundant_flag = true;//Rules with PT=* ----> PT=val
//	}
//	printf("\nNo. of shadowed rules with PT = *, %d", shadowed_rules_ctr);
//
//}
//
//bool isCompatible(unsigned long long int bv1, unsigned long long int bm1, unsigned long long int bv2, unsigned long long int bm2) {
//	for (int i = 1; i <= encodedRuleLen; i++) {
//		if (((bm1 >> (encodedRuleLen - i)) & 1) == 1 && ((bm2 >> (encodedRuleLen - i)) & 1) == 0) {
//			return false;
//		}
//		else if (((bm1 >> (encodedRuleLen - i)) & 1) == 1 && ((bm2 >> (encodedRuleLen - i)) & 1) == 1) {
//			if (((bv1 >> (encodedRuleLen - i)) & 1) != ((bv2 >> (encodedRuleLen - i)) & 1))
//				return false;
//		}
//	}
//	return true;
//}
//
//void bram(list<int> &indices) {
//	list<int> bram_rules;
//	int sa_threshold = (15 - codelenPT) / 2;
//	int da_threshold = 15 - codelenPT - sa_threshold;
//	for (list<int>::iterator it = indices.begin(); it != indices.end();) {
//		if (table[*it].mask_PT <= 7 && table[*it].mask_SA <= sa_threshold && table[*it].mask_DA <= da_threshold) {
//			bram_rules.push_back(*it);
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//		}
//		else {
//			it++;
//		}
//	}
//	fill(begin(bram_block), begin(bram_block) + 32768, -1);
//	//Iterate through the list in ascending order of priority. If bram_block[index] is empty assign index 
//	//else higher priority rule already assigned
//	for (list<int>::iterator it = bram_rules.begin(); it != bram_rules.end();it++) {
//		int table_index = *it;
//		int prefixlength_SA = sa_threshold - table[table_index].mask_SA;//number of non-significant bits
//		int prefixlength_DA = da_threshold - table[table_index].mask_DA;
//		int prefixlength_PT = codelenPT - table[table_index].mask_PT;
//		
//		int base_SA = 0;
//		int bit_pos = 14;
//		for (int j = 1; j <= table[table_index].mask_SA; j++, bit_pos--) {//mask_SA  will be less then the threshold
//			base_SA += pow(2, bit_pos)*((table[table_index].codeword_SA >> (codelenSA - j) ) & 1);
//		}
//
//		bit_pos = 14 - sa_threshold;
//		int base_DA = 0;
//		for (int j = 1; j <= table[table_index].mask_DA; j++, bit_pos--) {
//			base_DA += pow(2, bit_pos)*((table[table_index].codeword_DA >> (codelenDA - j)) & 1);
//		}
//
//		bit_pos = 14 - sa_threshold - da_threshold;
//		int base_PT = 0;
//		for (int j = 1; j <= table[table_index].mask_PT; j++, bit_pos--) {
//			base_PT += pow(2, bit_pos)*((table[table_index].codeword_PT >> (codelenPT - j)) & 1);
//		}
//
//		for (int i = 0; i < pow(2, prefixlength_SA); i++) {
//			int SAindex = base_SA;
//			SAindex += i * pow(2, da_threshold + codelenPT);
//			for (int j = 0; j < pow(2, prefixlength_DA); j++) {
//				int DAindex = SAindex + base_DA;
//				DAindex += j * pow(2, codelenPT);
//				for (int k = 0; k < pow(2, prefixlength_PT); k++) {
//					int index = DAindex + base_PT;
//					index += k;
//					if (bram_block[index] == -1) {
//						bram_block[index] = table_index;
//						table[table_index].assigned_memory_unit = 0;
//					}
//				}
//			}
//		}
//	}
//	printf("\nNo. of rules handled by the special block = %d\n", bram_rules.size());
//	FILE *temp = freopen("shaata.txt", "w", stdout);
//	for (int i = 0; i < 32768; i++) {
//		printf("%d.\t%d\n", i, bram_block[i]);
//	}
//	fflush(temp);
//	freopen("CON", "w", stdout);
//}
//
////int one_level_bit_selection(list<int> &indices) {//returns number of memory_units
////	int memory_units = 0;
////	double threshold = 0.2;
////	int distinctValues[4];
////	int lsb_position[4];
////	int length[4];
////	int originalIndex[4];
////	distinctValues[0] = sizeSA;
////	lsb_position[0] = codelenPT + codelenDP + codelenSP + codelenDA;
////	length[0] = codelenSA;
////	originalIndex[0] = 0;
////	distinctValues[1] = sizeDA;
////	lsb_position[1] = codelenPT + codelenDP + codelenSP;
////	length[1] = codelenDA;
////	originalIndex[1] = 1;
////	distinctValues[2] = sizeSP;
////	lsb_position[2] = codelenPT + codelenDP;
////	length[2] = codelenSP;
////	originalIndex[2] = 2;
////	distinctValues[3] = sizePT;
////	lsb_position[3] = codelenPT;
////	length[3] = codelenDP;
////	originalIndex[3] = 3;
////
////	for (int i = 0; i < 3; i++) {//bubble sort. sorting all arrays based on the number of distinct elements
////		for (int j = 0; j < 3 - i; j++) {
////			if (distinctValues[j] < distinctValues[j + 1]) {
////				int temp = distinctValues[j];
////				distinctValues[j] = distinctValues[j + 1];
////				distinctValues[j + 1] = temp;
////				temp = lsb_position[j];
////				lsb_position[j] = lsb_position[j + 1];
////				lsb_position[j + 1] = temp;
////				temp = length[j];
////				length[j] = length[j + 1];
////				length[j + 1] = temp;
////				temp = originalIndex[j];
////				originalIndex[j] = originalIndex[j + 1];
////				originalIndex[j + 1] = temp;
////			}
////		}
////	}
////	int combinations[40][4] = { 0 };//SA,DA,SP,DP
////	int ctr = 0;
////	if (sizeSA > sizeDA) {
////		combinations[0][1] = 10;
////	}
////	else {
////		combinations[0][0] = 10;
////	}
////	ctr = 1;
////	for (int i = 0; i < ctr; i++) {
////		int unit[1024][2];
////		for (int k = 0; k < 1024; k++)
////			for (int j = 0; j < 2; j++)
////				unit[k][j] = -1;
////
////		int rule_ctr = 0;
////		list<int> temp_indices = indices;
////		for (list<int>::iterator it = temp_indices.begin(); it != temp_indices.end();) {
////			int index = selected_index(combinations[i], table[*it].bv, table[*it].bm);
////			if (index == -1) {
////				it++;
////				continue;
////			}
////			if (unit[index][0] == -1) {
////				unit[index][0] = *it;
////				rule_ctr++;
////				int temp = *it;
////				it++;
////				temp_indices.remove(temp);
////			}
////			else if (unit[index][1] == -1) {
////				if (table[unit[index][0]].priority >= table[*it].priority) {
////					unit[index][1] = *it;
////				}
////				else {
////					unit[index][1] = unit[index][0];
////					unit[index][0] = *it;
////				}
////				rule_ctr++;
////				table[*it].assigned_memory_unit = memory_units + 1;
////				int temp = *it;
////				it++;
////				temp_indices.remove(temp);
////			}
////			else {
////				if (table[unit[index][0]].unused_bits < table[unit[index][1]].unused_bits) {
////					if (table[unit[index][0]].unused_bits < table[*it].unused_bits) {
////						temp_indices.push_back(unit[index][0]);
////						table[unit[index][0]].assigned_memory_unit = -1;
////						unit[index][0] = *it;
////						if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
////							int temp_val = unit[index][0];
////							unit[index][0] = unit[index][1];
////							unit[index][1] = temp_val;
////						}
////						int temp = *it;
////						table[*it].assigned_memory_unit = memory_units + 1;
////						it++;
////						temp_indices.remove(temp);
////					}
////					else {
////						it++;
////					}
////				}
////				else {
////					if (table[unit[index][1]].unused_bits < table[*it].unused_bits) {
////						temp_indices.push_back(unit[index][1]);
////						table[unit[index][1]].assigned_memory_unit = -1;
////						unit[index][1] = *it;
////						if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
////							int temp_val = unit[index][0];
////							unit[index][0] = unit[index][1];
////							unit[index][1] = temp_val;
////						}
////						int temp = *it;
////						table[*it].assigned_memory_unit = memory_units + 1;
////						it++;
////						temp_indices.remove(temp);
////					}
////					else {
////						it++;
////					}
////				}
////			}
////		}
////		if ((rule_ctr / 2048.0) >= threshold) {
////			indices = temp_indices;
////			memory_units++;
////			printf("\n%d,%d,%d,%d\t%d", combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], rule_ctr);
////		}	
////	}
////	ctr = 0;
////	threshold = 0.35;
////	memset(combinations[0], 0, sizeof(int) * 4);
////	memset(combinations[1], 0, sizeof(int) * 4);
////	for (int i = 0; i < 3; i++) {//only checking the first three fields,  10 bits if possible
////		if (length[i] >= 10)
////			combinations[ctr++][originalIndex[i]] = 10;
////	}
////	//for (int k = 5; k < 9; k++) {//combination of the first two fields only
////	//	if (length[0] >= k && length[1] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[0]] = k;
////	//		combinations[ctr++][originalIndex[1]] = 10 - k;
////	//	}
////	//	if (k == 5)
////	//		continue;
////	//	if (length[1] >= k && length[0] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[1]] = k;
////	//		combinations[ctr++][originalIndex[0]] = 10 - k;
////	//	}
////	//}
////	for (int k = 5; k < 9; k++) {
////		for (int i = 0; i < 3; i++) {
////			for (int j = 1; j < 3; j++) {
////				if (k == 5 && j == 2)
////					break;
////				if (length[i] >= k && length[((i + j) % 3)] >= (10 - k)) {
////					combinations[ctr][originalIndex[i]] = k;
////					combinations[ctr++][originalIndex[(i + j) % 3]] = 10 - k;
////				}
////			}
////		}
////	}
////
////	for (int k = 6; k > 2; k--) {//combinations of three fields.
////		for (int i = 0; i < 3; i++) {
////			if (length[i] >= k) {
////				int val1 = (10 - k) / 2;
////				int val2 = 10 - k - ((10 - k) / 2);
////				if (k == val1 || k == val2)
////					continue;
////				if (length[(i + 1) % 3] >= val1 && length[(i - 1) >= 0 ? (i - 1) : 2] >= val2) {
////					combinations[ctr][originalIndex[i]] = k;
////					combinations[ctr][originalIndex[(i + 1) % 3]] = val1;
////					combinations[ctr++][originalIndex[((i - 1) >= 0 ? (i - 1) : 2)]] = val2;
////				}
////				if (val1 == val2)
////					continue;
////				if (length[(i + 1) % 3] >= val2 && length[(i - 1) >= 0 ? (i - 1) : 2] >= val1) {
////					combinations[ctr][originalIndex[i]] = k;
////					combinations[ctr][originalIndex[(i + 1) % 3]] = val2;
////					combinations[ctr++][originalIndex[((i - 1) >= 0 ? (i - 1) : 2)]] = val1;
////				}
////			}
////		}
////	}
////	//for (int k = 5; k < 9; k++) {//combination of the first two fields only
////	//	if (length[0] >= k && length[2] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[0]] = k;
////	//		combinations[ctr++][originalIndex[2]] = 10 - k;
////	//	}
////	//	if (length[1] >= k && length[2] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[1]] = k;
////	//		combinations[ctr++][originalIndex[2]] = 10 - k;
////	//	}
////	//	if (k == 5)
////	//		continue;
////	//	if (length[2] >= k && length[0] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[2]] = k;
////	//		combinations[ctr++][originalIndex[0]] = 10 - k;
////	//	}
////	//	if (length[2] >= k && length[1] >= (10 - k)) {
////	//		combinations[ctr][originalIndex[2]] = k;
////	//		combinations[ctr++][originalIndex[1]] = 10 - k;
////	//	}
////	//}
////	int i = 0;
////	int combination_ctr = 0;
////	do {
////		int unit[1024][2];
////		for (int k = 0; k < 1024; k++)
////			for (int j = 0; j < 2; j++)
////				unit[k][j] = -1;
////
////		int rule_ctr = 0;
////		list<int> temp_indices = indices;
////		for (list<int>::iterator it = temp_indices.begin(); it != temp_indices.end();) {
////			int index = selected_index(combinations[i], table[*it].bv, table[*it].bm);
////			if (index == -1) {
////				it++;
////				continue;
////			}
////			if (unit[index][0] == -1) {
////				unit[index][0] = *it;
////				rule_ctr++;
////				int temp = *it;
////				it++;
////				temp_indices.remove(temp);
////			}
////			else if (unit[index][1] == -1) {
////				if (table[unit[index][0]].priority >= table[*it].priority) {
////					unit[index][1] = *it;
////				}
////				else {
////					unit[index][1] = unit[index][0];
////					unit[index][0] = *it;
////				}
////				rule_ctr++;
////				table[*it].assigned_memory_unit = memory_units + 1;
////				int temp = *it;
////				it++;
////				temp_indices.remove(temp);
////			}
////			else {
////				if (table[unit[index][0]].unused_bits < table[unit[index][1]].unused_bits) {
////					if (table[unit[index][0]].unused_bits < table[*it].unused_bits) {
////						temp_indices.push_back(unit[index][0]);
////						table[unit[index][0]].assigned_memory_unit = -1;
////						unit[index][0] = *it;
////						if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
////							int temp_val = unit[index][0];
////							unit[index][0] = unit[index][1];
////							unit[index][1] = temp_val;
////						}
////						int temp = *it;
////						table[*it].assigned_memory_unit = memory_units + 1;
////						it++;
////						temp_indices.remove(temp);
////					}
////					else {
////						it++;
////					}
////				}
////				else {
////					if (table[unit[index][1]].unused_bits < table[*it].unused_bits) {
////						temp_indices.push_back(unit[index][1]);
////						table[unit[index][1]].assigned_memory_unit = -1;
////						unit[index][1] = *it;
////						if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
////							int temp_val = unit[index][0];
////							unit[index][0] = unit[index][1];
////							unit[index][1] = temp_val;
////						}
////						int temp = *it;
////						table[*it].assigned_memory_unit = memory_units + 1;
////						it++;
////						temp_indices.remove(temp);
////					}
////					else {
////						it++;
////					}
////				}
////			}
////		}
////		combination_ctr++;
////		if ((rule_ctr / 2048.0) >= threshold) {
////			if (combination_ctr > 1 && (rule_ctr / 2048.0) < 0.4) {
////				i++;
////				combination_ctr = 0;
////			}
////			else {
////				indices = temp_indices;
////				memory_units++;
////				printf("\n%d,%d,%d,%d\t%d", combinations[i][0], combinations[i][1], combinations[i][2], combinations[i][3], rule_ctr);
////			}
////		}
////		else {
////			i++;
////			combination_ctr = 0;
////		}
////	} while (i<ctr);
////	return memory_units;
////}
//
//int one_level_bit_selection(list<int> &indices) {
//	int SA_bucket[1024] = { 0 };
//	int DA_bucket[1024] = { 0 };
//	int DP_bucket[1024] = { 0 };
//
//	int SA_suffix = min((int)(ceil(log(sizeSA) / log(2))), 10);
//	int DA_suffix = min((int)(ceil(log(sizeDA) / log(2))), 10);
//	int DP_suffix = min((int)(ceil(log(sizeDP) / log(2))), 10);
//	int SA_selected_bits[4] = { SA_suffix,0,0,0 };
//	int DA_selected_bits[4] = { 0,DA_suffix,0,0 };
//	int DP_selected_bits[4] = { 0,0,0,DP_suffix };
//
//	int SA_weight = 0;
//	int DA_weight = 0;
//
//	int SA_count = 0;
//	int DA_count = 0;
//	int DP_count = 0;
//
//	int SA_total = 0;
//	int DA_total = 0;
//	int DP_total = 0;
//
//	for (list<int>::iterator it = indices.begin(); it != indices.end(); it++) {
//		int index = selected_index(SA_selected_bits, table[*it].bv, table[*it].bm);
//		if (index != -1) {
//			SA_bucket[index]++;
//			SA_total++;
//		}
//		index = selected_index(DA_selected_bits, table[*it].bv, table[*it].bm);
//		if (index != -1) {
//			DA_bucket[index]++;
//			DA_total++;
//		}
//		index = selected_index(DP_selected_bits, table[*it].bv, table[*it].bm);
//		if (index != -1) {
//			DP_bucket[index]++;
//			DP_total++;
//		}
//	}
//
//	for (int i = 0; i < 1024; i++) {
//		if (SA_bucket[i] > 0) {
//			if (SA_bucket[i] == 1) {
//				SA_weight++;
//			}
//			else {
//				SA_weight += 2;
//			}
//			SA_count++;
//		}
//		if (DA_bucket[i] > 0) {
//			if (DA_bucket[i] == 1) {
//				DA_weight++;
//			}
//			else {
//				DA_weight += 2;
//			}
//			DA_count++;
//		}
//		if (DP_bucket[i] > 0) {
//			DP_count++;
//		}
//	}
//	int initial_max = ceil(max(SA_weight, DA_weight)* 0.8);
//	int match_unit_ctr = 0;
//	do {
//		int weight_threshold = min(initial_max, 1000);
//		bool flag = false;
//		int selected_bits[4] = { 0 };
//		if (SA_weight > weight_threshold && DA_weight > weight_threshold) {
//			if (SA_weight < DA_weight) {
//				selected_bits[0] = SA_suffix;
//			}
//			else {
//				selected_bits[1] = DA_suffix;
//			}
//			flag = true;
//			int unit[1024][2];
//			int count = mapRules(indices, selected_bits, unit);
//			printf("\n%d,%d,%d,%d\t%d", selected_bits[0], selected_bits[1], selected_bits[2], selected_bits[3], count);
//		}
//		else if (SA_weight > weight_threshold) {
//			flag = true;
//			selected_bits[0] = SA_suffix;
//			int unit[1024][2];
//			int count = mapRules(indices, selected_bits, unit);
//			printf("\n%d,%d,%d,%d\t%d", selected_bits[0], selected_bits[1], selected_bits[2], selected_bits[3], count);
//		}
//		else if (DA_weight > weight_threshold) {
//			flag = true;
//			selected_bits[1] = DA_suffix;
//			int unit[1024][2];
//			int count = mapRules(indices, selected_bits, unit);
//			printf("\n%d,%d,%d,%d\t%d", selected_bits[0], selected_bits[1], selected_bits[2], selected_bits[3], count);
//		}
//		else {
//			int selected_bits1[4] = { 0 };
//			int selected_bits2[4] = { 0 };
//			int selected_bits3[4] = { 0 };
//			int SA_bits = (int)((double)SA_suffix / (SA_suffix + DA_suffix) * 10.0);
//			int DA_bits = 10 - SA_bits;
//			selected_bits1[0] = SA_bits;
//			selected_bits1[1] = DA_bits;
//			if (match_unit_ctr >= 3 && DP_count > 16 && DP_total > 500) {
//				if (SA_count > DA_count) {
//					int FA_bits = (int)((double)SA_suffix / (SA_suffix + DP_suffix) * 10.0);
//					int DP_bits = 10 - FA_bits;
//					selected_bits2[0] = FA_bits;
//					selected_bits2[3] = DP_bits;
//				}
//				else {
//					int FA_bits = (int)((double)DA_suffix / (DA_suffix + DP_suffix) * 10.0);
//					int DP_bits = 10 - FA_bits;
//					selected_bits2[1] = FA_bits;
//					selected_bits2[3] = DP_bits;
//				}
//				SA_bits = (int)(10.0 *SA_suffix / (SA_suffix + DA_suffix + DP_suffix));
//				DA_bits = (int)(10.0 *DA_suffix / (DA_suffix + SA_suffix + DP_suffix));
//				int DP_bits = 10 - (SA_bits + DA_bits);
//				selected_bits3[0] = SA_bits;
//				selected_bits3[1] = DA_bits;
//				selected_bits3[3] = DP_bits;
//			}
//			list<int> temp1 = indices;
//			list<int> temp2 = indices;
//			list<int> temp3 = indices;
//			int unit1[1024][2];
//			int unit2[1024][2];
//			int unit3[1024][2];
//			int count1 = mapRules(temp1, selected_bits1, unit1);
//			int count2 = mapRules(temp2, selected_bits2, unit2);
//			int count3 = mapRules(temp3, selected_bits3, unit3);
//			if (count1 >= count2 && count1 >= count3 && count1 >= 500) {
//				indices = temp1;
//				flag = true;
//				printf("\n%d,%d,%d,%d\t%d", selected_bits1[0], selected_bits1[1], selected_bits1[2], selected_bits1[3], count1);
//			}
//			else if (count2 >= count1 && count2 >= count3 && count2 >= 500) {
//				indices = temp2;
//				flag = true;
//				printf("\n%d,%d,%d,%d\t%d", selected_bits2[0], selected_bits2[1], selected_bits2[2], selected_bits2[3], count2);
//			}
//			else if (count3 >= 500) {
//				indices = temp3;
//				flag = true;
//				printf("\n%d,%d,%d,%d\t%d", selected_bits3[0], selected_bits3[1], selected_bits3[2], selected_bits3[3], count3);
//			}
//		}
//		if (flag) {
//			memset(SA_bucket, 0, sizeof(int) * 1024);
//			memset(DA_bucket, 0, sizeof(int) * 1024);
//			memset(DP_bucket, 0, sizeof(int) * 1024);
//			if (SA_count / pow(2, SA_suffix) < 0.33) {
//				SA_suffix--;
//				for (int i = 0; i < pow(2, SA_suffix); i++) {
//					SA_bucket[i] += SA_bucket[(int)(i + pow(2, SA_suffix))];
//				}
//			}
//			if (DA_count / pow(2, DA_suffix) < 0.33) {
//				DA_suffix--;
//				for (int i = 0; i < pow(2, SA_suffix); i++) {
//					DA_bucket[i] += DA_bucket[(int)(i + pow(2, SA_suffix))];
//				}
//			}
//			if (DP_count / pow(2, DP_suffix) < 0.33) {
//				DP_suffix--;
//				for (int i = 0; i < pow(2, DP_suffix); i++) {
//					DP_bucket[i] += DP_bucket[(int)(i + pow(2, DP_suffix))];
//				}
//			}
//			SA_total = 0;
//			DA_total = 0;
//			DP_total = 0;
//			SA_weight = 0;
//			DA_weight = 0;
//			SA_count = 0;
//			DA_count = 0;
//			DP_count = 0;
//			SA_selected_bits[0] = SA_suffix;
//			DA_selected_bits[1] = DA_suffix;
//			DP_selected_bits[3] = DP_suffix;	
//			for (list<int>::iterator it = indices.begin(); it != indices.end(); it++) {
//				int index = selected_index(SA_selected_bits, table[*it].bv, table[*it].bm);
//				if (index != -1) {
//					SA_bucket[index]++;
//					SA_total++;
//				}
//				index = selected_index(DA_selected_bits, table[*it].bv, table[*it].bm);
//				if (index != -1) {
//					DA_bucket[index]++;
//					DA_total++;
//				}
//				index = selected_index(DP_selected_bits, table[*it].bv, table[*it].bm);
//				if (index != -1) {
//					DP_bucket[index]++;
//					DP_total++;
//				}
//			}
//			for (int i = 0; i < 1024; i++) {
//				if (SA_bucket[i] > 0) {
//					if (SA_bucket[i] == 1) {
//						SA_weight++;
//					}
//					else {
//						SA_weight += 2;
//					}
//					SA_count++;
//				}
//				if (DA_bucket[i] > 0) {
//					if (DA_bucket[i] == 1) {
//						DA_weight++;
//					}
//					else {
//						DA_weight += 2;
//					}
//					DA_count++;
//				}
//				if (DP_bucket[i] > 0) {
//					DP_count++;
//				}
//			}
//			match_unit_ctr++;
//		}
//		else {
//			break;
//		}
//	} while (true);
//	return match_unit_ctr;
//}
//
//int mapRules(list<int> &indices, int selected_bits[4], int unit[1024][2]) {
//	int rule_ctr = 0;
//	for (int k = 0; k < 1024; k++)
//		for (int j = 0; j < 2; j++)
//			unit[k][j] = -1;
//	for (list<int>::iterator it = indices.begin(); it != indices.end(); ) {
//		int index = selected_index(selected_bits, table[*it].bv, table[*it].bm);
//		if (index == -1) {
//			it++;
//			continue;
//		}
//		if (unit[index][0] == -1) {
//			unit[index][0] = *it;
//			rule_ctr++;
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//		}
//		else if (unit[index][1] == -1) {
//			if (table[unit[index][0]].priority >= table[*it].priority) {
//				unit[index][1] = *it;
//			}
//			else {
//				unit[index][1] = unit[index][0];
//				unit[index][0] = *it;
//			}
//			rule_ctr++;
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//		}
//		else {
//			if (table[unit[index][0]].unused_bits < table[unit[index][1]].unused_bits) {
//				if (table[unit[index][0]].unused_bits < table[*it].unused_bits) {
//					indices.push_back(unit[index][0]);
//					table[unit[index][0]].assigned_memory_unit = -1;
//					unit[index][0] = *it;
//					if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
//						int temp_val = unit[index][0];
//						unit[index][0] = unit[index][1];
//						unit[index][1] = temp_val;
//					}
//					int temp = *it;
//					it++;
//					indices.remove(temp);
//				}
//				else {
//					it++;
//				}
//			}
//			else {
//				if (table[unit[index][1]].unused_bits < table[*it].unused_bits) {
//					indices.push_back(unit[index][1]);
//					table[unit[index][1]].assigned_memory_unit = -1;
//					unit[index][1] = *it;
//					if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
//						int temp_val = unit[index][0];
//						unit[index][0] = unit[index][1];
//						unit[index][1] = temp_val;
//					}
//					int temp = *it;
//					it++;
//					indices.remove(temp);
//				}
//				else {
//					it++;
//				}
//			}
//		}
//	}
//	return rule_ctr;
//}
//
//int two_level_bit_selection(list<int> &indices) {
//	int memory_units = 0;
//	while (!indices.empty()) {
//		int *rc0 = new int[encodedRuleLen];
//		memset(rc0, 0, sizeof(int)*encodedRuleLen);
//		int *rc1 = new int[encodedRuleLen];
//		memset(rc1, 0, sizeof(int)*encodedRuleLen);
//		int *rs = new int[encodedRuleLen];
//		memset(rs, 0, sizeof(int)*encodedRuleLen);
//		double *BF = new double[encodedRuleLen];
//		fill(BF, BF + encodedRuleLen, 0);
//		for (list<int>::iterator it = indices.begin(); it != indices.end(); it++) {
//			for (int i = 0; i < encodedRuleLen; i++) {
//				if ((table[*it].bm >> i & 1) == 1) {
//					if ((table[*it].bv >> i & 1) == 0) {
//						rc0[i]++;
//					}
//					else {
//						rc1[i]++;
//					}
//					rs[i]++;
//				}
//			}
//		}
//		int b0 = 0;
//		double largest = 0;
//		for (int i = 0; i < encodedRuleLen; i++) {
//			BF[i] = ((double)min(rc0[i], rc1[i])) / indices.size();
//			if (BF[i] > largest || (BF[i] == largest && rs[i]>0)) {//towards the end rules have similar set bits. 
//				//when selecting b0 and b1 we have to make sure that the BF is not 0, otherwise it would just choose the 2 msb. 
//				//and the remaining rules may never get assigned
//				largest = BF[i];
//				b0 = i;
//			}
//		}
//		list<int> rules0;
//		list<int> rules1;
//		list<int> rules_wildcard;//rules with selected bits = *
//		for (list<int>::iterator it = indices.begin(); it != indices.end();it++) {
//			if ((table[*it].bm >> b0 & 1) == 1) {
//				if ((table[*it].bv >> b0 & 1) == 0) {
//					rules0.push_back(*it);
//				}
//				else {
//					rules1.push_back(*it);
//				}
//			}
//			else {
//				rules_wildcard.push_back(*it);
//			}
//		}
//		memset(rc0, 0, sizeof(int)*encodedRuleLen);
//		memset(rc1, 0, sizeof(int)*encodedRuleLen);
//		memset(rs, 0, sizeof(int)*encodedRuleLen);
//		for (list<int>::iterator it = rules0.begin(); it != rules0.end(); it++) {
//			for (int i = 0; i < encodedRuleLen; i++) {
//				if ((table[*it].bm >> i & 1) == 1) {
//					if ((table[*it].bv >> i & 1) == 0) {
//						rc0[i]++;
//					}
//					else {
//						rc1[i]++;
//					}
//					rs[i]++;
//				}
//			}
//		}
//		fill(BF, BF + encodedRuleLen, 0);
//		for (int i = 0; i < encodedRuleLen; i++) {
//			if(rules0.size()>0)
//				BF[i] = min(rc0[i], rc1[i]) / rules0.size();
//		}
//		memset(rc0, 0, sizeof(int)*encodedRuleLen);
//		memset(rc1, 0, sizeof(int)*encodedRuleLen);
//		for (list<int>::iterator it = rules1.begin(); it != rules1.end(); it++) {
//			for (int i = 0; i < encodedRuleLen; i++) {
//				if ((table[*it].bm >> i & 1) == 1) {
//					if ((table[*it].bv >> i & 1) == 0) {
//						rc0[i]++;
//					}
//					else {
//						rc1[i]++;
//					}
//					rs[i]++;
//				}
//			}
//		}
//		for (int i = 0; i < encodedRuleLen; i++) {
//			if(rules1.size()>0)
//				BF[i] += ((double)min(rc0[i], rc1[i])) / rules1.size();
//		}
//		BF[b0] = -1;
//		int b1 = 0;
//		largest = 0.0;
//		for (int i = 0; i < encodedRuleLen; i++) {
//			if (BF[i] > largest || (BF[i] == largest && rs[i]>0)) {
//				largest = BF[i];
//				b1 = i;
//			}
//		}
//		list<int> rules[4];
//		for (list<int>::iterator it = rules0.begin(); it != rules0.end();it++) {
//			if (table[*it].bm >> b1 & 1 == 1) {
//				if ((table[*it].bv >> b1 & 1) == 0) {
//					rules[0].push_back(*it);
//				}
//				else {
//					rules[1].push_back(*it);
//				}
//			}
//			else {
//				rules_wildcard.push_back(*it);
//			}
//		}
//		for (list<int>::iterator it = rules1.begin(); it != rules1.end(); it++) {
//			if (table[*it].bm >> b1 & 1 == 1) {
//				if ((table[*it].bv >> b1 & 1) == 0) {
//					rules[2].push_back(*it);
//				}
//				else {
//					rules[3].push_back(*it);
//				}
//			}
//			else {
//				rules_wildcard.push_back(*it);
//			}
//		}
//		int selected_bits[4][8];
//		list<int> wildcard[4];
//		for (int i = 0; i < 4; i++) {
//			fill(selected_bits[i], selected_bits[i] + 8, -1);
//			list<int> *temp_rules = new list<int>[pow(2, 8)];
//			temp_rules[0] = rules[i];
//			bool flag = true;
//			for (int j = 0; j < 8 && flag; j++) {
//				list<int>* temp_arr = new list<int>[pow(2, j + 1)];
//				fill(BF, BF + encodedRuleLen, 0);
//				for (int k = 0; k < pow(2, j); k++) {
//					memset(rc0, 0, sizeof(int)*encodedRuleLen);
//					memset(rc1, 0, sizeof(int)*encodedRuleLen);
//					for (list<int>::iterator it = temp_rules[k].begin(); it != temp_rules[k].end(); it++) {
//						for (int l = 0; l < encodedRuleLen; l++) {
//							if ((table[*it].bm >> l & 1) == 1) {
//								if ((table[*it].bv >> l & 1) == 0) {
//									rc0[l]++;
//								}
//								else {
//									rc1[l]++;
//								}
//							}
//						}
//					}
//					for (int l = 0; l < encodedRuleLen; l++) {
//						if(rules[i].size() > 0)
//							BF[l] += (((double)min(rc0[l], rc1[l])) / temp_rules[k].size());
//					}
//				}
//				largest = 0;
//				for (int l = codelenPT; l < encodedRuleLen; l++) {
//					if (BF[l] > largest) {
//						largest = BF[l];
//						selected_bits[i][j] = l;
//					}
//				}
//				if (selected_bits[i][j] == -1) {
//					flag = false;
//					break;
//				}
//				for (int k = 0; k < pow(2, j); k++) {
//					for (list<int>::iterator it = temp_rules[k].begin(); it != temp_rules[k].end(); it++) {
//						if ((table[*it].bm >> selected_bits[i][j] & 1) == 1) {
//							if ((table[*it].bv >> selected_bits[i][j] & 1) == 0) {
//								temp_arr[2*k].push_back(*it);
//							}
//							else {
//								temp_arr[2*k+1].push_back(*it);
//							}
//						}
//						else {
//							wildcard[i].push_back(*it);
//						}
//					}
//				}
//				for (int k = 0; k < pow(2, j + 1); k++) {
//					temp_rules[k] = temp_arr[k];
//				}
//				delete []temp_arr;
//			}
//			rules[i] = list<int>();
//			for (int j = 0; j < pow(2, 8); j++) {
//				for (list<int>::iterator it = temp_rules[j].begin(); it != temp_rules[j].end(); it++) {
//					rules[i].push_back(*it);
//				}
//			}
//			delete []temp_rules;
//		}
//		
//		for (int k = 0; k < 4; k++) {
//			for (int i = 0; i < 8; i++) {
//				for (int j = 0; j < 7 - i; j++) {
//					if (selected_bits[k][j] > selected_bits[k][j + 1]) {//arr[0] has the smallest index
//						int tmp = selected_bits[k][j];
//						selected_bits[k][j] = selected_bits[k][j + 1];
//						selected_bits[k][j + 1] = tmp;
//					}
//				}
//			}
//		}
//
//		int unit[1024][2];
//		for (int i = 0; i < 1024; i++)
//			for (int j = 0; j < 2; j++)
//				unit[i][j] = -1;
//		int offset[4] = { 0,256,512,768 };
//		if (b1 > b0) {//b0 is the MSB
//			offset[1] = 512;
//			offset[2] = 256;
//		}
//		int rule_ctr = 0;
//		for (int i = 0; i < 4; i++) {
//			rule_ctr += assign_indices(rules[i], selected_bits[i], offset[i], unit, wildcard[i]);
//		}
//		indices = rules_wildcard;
//		for (int i = 0; i < 4; i++) {
//			for (list<int>::iterator it = rules[i].begin(); it != rules[i].end(); it++) {
//				indices.push_back(*it);
//			}
//			for (list<int>::iterator it = wildcard[i].begin(); it != wildcard[i].end(); it++) {
//				indices.push_back(*it);
//			}
//		}
//		memory_units++;
//		printf("b0 = %d, b1 = %d \t%d\n", b0, b1,rule_ctr);
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 8; j++) {
//				printf("%d,", selected_bits[i][j]);
//			}
//			printf("\n");
//		}
//	}
//	return memory_units;
//}
//
//int assign_indices(list<int> &indices,int selected_bits[8],int offset, int unit[1024][2],list<int> &wildcard) {//returns number of rules assigned
//	int rule_ctr = 0;
//	for (list<int>::iterator it = indices.begin(); it != indices.end();) {
//		int index = offset;
//		index += selected_index_2(selected_bits, table[*it].bv, table[*it].bm);
//		if (index == -1) {
//			wildcard.push_back(*it);
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//			continue;
//		}
//		if (unit[index][0] == -1) {
//			unit[index][0] = *it;
//			rule_ctr++;
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//		}
//		else if (unit[index][1] == -1) {
//			if (table[unit[index][0]].priority >= table[*it].priority) {
//				unit[index][1] = *it;
//			}
//			else {
//				unit[index][1] = unit[index][0];
//				unit[index][0] = *it;
//			}
//			rule_ctr++;
//			int temp = *it;
//			it++;
//			indices.remove(temp);
//		}
//		else {
//			if (table[unit[index][0]].unused_bits < table[unit[index][1]].unused_bits) {
//				if (table[unit[index][0]].unused_bits < table[*it].unused_bits) {
//					indices.push_back(unit[index][0]);
//					unit[index][0] = *it;
//					if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
//						int temp_val = unit[index][0];
//						unit[index][0] = unit[index][1];
//						unit[index][1] = temp_val;
//					}
//					int temp = *it;
//					it++;
//					indices.remove(temp);
//				}
//				else {
//					it++;
//				}
//			}
//			else {
//				if (table[unit[index][1]].unused_bits < table[*it].unused_bits) {
//					indices.push_back(unit[index][1]);
//					unit[index][1] = *it;
//					if (table[unit[index][0]].priority < table[unit[index][1]].priority) {
//						int temp_val = unit[index][0];
//						unit[index][0] = unit[index][1];
//						unit[index][1] = temp_val;
//					}
//					int temp = *it;
//					it++;	
//					indices.remove(temp);
//				}
//				else {
//					it++;
//				}
//			}
//		}
//	}
//	wildcard.sort([](const int &a, const int &b) { return table[a].unused_bits > table[b].unused_bits; });
//	for (list<int>::iterator it = wildcard.begin(); it != wildcard.end();) {
//		int wildcard_bits = 0;
//		for (int i = 0; i < 8; i++) {
//			if (selected_bits[i] == -1)
//				continue;
//			if (((table[*it].bm >> selected_bits[i]) & 1) == 0) {
//				wildcard_bits++;
//			}
//		}
//		int *bit_pos = new int[wildcard_bits];
//		int ctr = 0;
//		for (int i = 0; i < 8; i++) {
//			if (selected_bits[i] == -1)
//				continue;
//			if (((table[*it].bm >> selected_bits[i]) & 1) == 0) {
//				bit_pos[ctr++] = selected_bits[i];
//			}
//		}
//		unsigned long long int *bvs = new unsigned long long int[pow(2,wildcard_bits)];
//		for (int i = 0; i < pow(2, wildcard_bits); i++) {
//			bvs[i] = table[*it].bv;
//		}
//		for (int i = 1; i <= wildcard_bits; i++) {//Emulating a truth table to get all possible values
//			int ctr = 0;
//			for (int j = 0; j < pow(2,wildcard_bits); j++) {
//				bvs[j] = bvs[j] ^ (1ULL << (encodedRuleLen - 1 - bit_pos[i - 1]));
//				ctr++;
//				if (ctr == i) {
//					j += ctr;
//					ctr = 0;
//				}
//			}
//		}
//		unsigned long long int temp_bm = 0xffffffffffffffff;//dummy mask to signify all bits
//		bool flag = true;
//		int *index_arr = new int[pow(2, wildcard_bits)];
//		for (int i = 0; i < pow(2, wildcard_bits) && flag; i++) {
//			index_arr[i] = selected_index_2(selected_bits, bvs[i], temp_bm) + offset;
//			if (!(unit[index_arr[i]][0] == -1 || unit[index_arr[i]][1] == -1)) {
//				flag = false;
//				break;
//			}
//		}
//		if (flag) {
//			for (int i = 0; i < pow(2, wildcard_bits); i++) {
//				if (unit[index_arr[i]][0] == -1) {
//					unit[index_arr[i]][0] = *it;
//				}
//				else {
//					if (table[unit[index_arr[i]][0]].priority < table[*it].priority) {
//						unit[index_arr[i]][1] = unit[index_arr[i]][1];
//						unit[index_arr[i]][0] = *it;
//					}
//					else {
//						unit[index_arr[i]][1] = *it;
//					}
//				}
//			}
//			int temp = *it;
//			it++;
//			wildcard.remove(temp);
//			rule_ctr++;
//		}
//		else {
//			it++;
//		}
//	}
//	return rule_ctr;
//}
//
//int selected_index_2(int selected_bits[8], const unsigned long long int&bv, const unsigned long long int &bm) {
//	int sum = 0;
//	int ctr = 0;
//	for (int i = 0; i < 8; i++) {
//		if (selected_bits[i] == -1) {
//			ctr++;
//			continue;
//		}
//		if ((bm >> (selected_bits[i]) & 1) == 0) {
//			return -1;
//		}
//		else {
//			sum += (pow(2, ctr++)*((bv >> selected_bits[i]) & 1));
//		}
//	}
//	return sum;
//}
//
//int selected_index(int selected_bits[4], const unsigned long long int &bv, const unsigned long long int &bm) {// if -1 is returned, at least one of the bits is a wildcard 
//	int sum = 0;
//	int ctr = 0;
//	int arr[4] = { codelenPT + codelenDP + codelenSP + codelenDA,codelenPT + codelenDP + codelenSP,codelenPT + codelenDP,codelenPT };
//	for (int i = 3; i >= 0; i--) {
//		for (int j = 0; j < selected_bits[i];j++) {
//			if ((bm >> (arr[i] + j) & 1) == 0) {
//				return -1;
//			}
//			else {
//				sum += (pow(2, ctr++)*((bv >> (arr[i] + j)) & 1));
//			}
//		}
//	}
//	return sum;
//}
//
//int assignRules() {
//	list<int> indices;
//	for (int i = 0; i < number_of_rules; i++) {
//		if (!table[i].redundant_flag) {
//			if (!table[i].PT_flag || table[i].secondary_index == -1) {
//				//Rules with PT = */value 
//				indices.push_back(i);
//			}
//		}
//	}
//	bram(indices);
//	int static_memory_units = one_level_bit_selection(indices);
//	printf("\nNumber of static blocks = %d\n", static_memory_units);
//	printf("Number of rules left = %d\n", indices.size());
//	int dynamic_memory_units = two_level_bit_selection(indices);
//	printf("Number of dynamic blocks = %d\n", dynamic_memory_units);
//	return static_memory_units+dynamic_memory_units;
//}
////end