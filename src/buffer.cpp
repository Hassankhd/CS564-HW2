/**
 * @author See Contributors.txt for code contributors and overview of BadgerDB.
 *
 * @section LICENSE
 * Copyright (c) 2012 Database Group, Computer Sciences Department, University
 * of Wisconsin-Madison.
 */

#include "buffer.h"

#include <iostream>
#include <memory>

#include "exceptions/bad_buffer_exception.h"
#include "exceptions/buffer_exceeded_exception.h"
#include "exceptions/hash_not_found_exception.h"
#include "exceptions/page_not_pinned_exception.h"
#include "exceptions/page_pinned_exception.h"

namespace badgerdb {

constexpr int HASHTABLE_SZ(int bufs) { return ((int)(bufs * 1.2) & -2) + 1; }

//----------------------------------------
// Constructor of the class BufMgr
//----------------------------------------

BufMgr::BufMgr(std::uint32_t bufs)
    : numBufs(bufs),
      hashTable(HASHTABLE_SZ(bufs)),
      bufDescTable(bufs),
      bufPool(bufs) {
  for (FrameId i = 0; i < bufs; i++) {
    bufDescTable[i].frameNo = i;
    bufDescTable[i].valid = false;
  }

  clockHand = bufs - 1;
}

/**
 * This method advances the clockHand to the next bit using modular
 * arithmetic to ensure the clock remains in the acceptable range
 */
void BufMgr::advanceClock() {
    this->clockHand = (this->clockHand + 1) % this->numBufs
}

void BufMgr::allocBuf(FrameId& frame) {

    // find free frame using clock algorithm

    // write page back to disk, dirty if necessary

    // if buffer frame has valid page in it, remove entry from hash table

    // Throw BufferExceededException if all buffer frames are pinned
}

void BufMgr::readPage(File& file, const PageId pageNo, Page*& page) {}

void BufMgr::unPinPage(File& file, const PageId pageNo, const bool dirty) {}

/**
 * Allocate a page within the buffer manager
 * @param file to be allocated in the buffer manager
 * @param pageNo is the page number that will be allocated
 * @param page that will be allocated
 *
 * Returns pageNo and page by updating the pointers
 */
void BufMgr::allocPage(File& file, PageId& pageNo, Page*& page) {
    Page*& newPage = file.allocatePage();
    int frameNo = bufDescTable[clockHand].frameNo;
    allocBuf(frameNo) // I think this is how I'm supposed to do this...

    // Wrap in try catch
    this->hashTable.insert(file, pageNo, frameNo);
    this->hashTable.Set(file, pageNo)

    // set pageNo and page?
}

void BufMgr::flushFile(File& file) {}

void BufMgr::disposePage(File& file, const PageId PageNo) {}

void BufMgr::printSelf(void) {
  int validFrames = 0;

  for (FrameId i = 0; i < numBufs; i++) {
    std::cout << "FrameNo:" << i << " ";
    bufDescTable[i].Print();

    if (bufDescTable[i].valid) validFrames++;
  }

  std::cout << "Total Number of Valid Frames:" << validFrames << "\n";
}

}  // namespace badgerdb
