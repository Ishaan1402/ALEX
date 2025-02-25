// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "zipf.h"

template <class T>
bool load_binary_data(T data[], int length, const std::string& file_path) {
  std::ifstream is(file_path.c_str(), std::ios::binary | std::ios::in);
    if(is.good()){
        std::cout << "Binary: The state of this stream is good (goodbit)" << std::endl;
    }
    else if(is.eof()){
        std::cout << "Binary: End of file error (eofbit)" << std::endl;
    }
    else if(is.bad()){
        std::cout << "Binary: Read/Write error (badbit)" << std::endl;
    }
    else if(is.fail()){
        std::cout << "Binary: Logical error (badbit)" << std::endl;
    }
    else{
        std::cout << "Binary: Unknown error with i/o" << std::endl;
    }
  if (!is.is_open()) {
    return false;
  }
  is.read(reinterpret_cast<char*>(data), std::streamsize(length * sizeof(T)));
  is.close();
  return true;
}

template <class T>
bool load_text_data(T array[], int length, const std::string& file_path) {
  std::ifstream is(file_path.c_str());
    if(is.good()){
        std::cout << "Text: The state of this stream is good (goodbit)" << std::endl;
    }
    else if(is.eof()){
        std::cout << "Text: End of file error (eofbit)" << std::endl;
    }
    else if(is.bad()){
        std::cout << "Text: Read/Write error (badbit)" << std::endl;
    }
    else if(is.fail()){
        std::cout << "Text: Logical error (badbit)" << std::endl;
    }
    else{
        std::cout << "Text: Unknown error with i/o" << std::endl;
    }
  if (!is.is_open()) {
    return false;
  }
  int i = 0;
  std::string str;
  while (std::getline(is, str) && i < length) {
    std::istringstream ss(str);
    ss >> array[i];
    i++;
  }
  is.close();
  return true;
}

template <class T>
T* get_search_keys(T array[], int num_keys, int num_searches) {
  std::mt19937_64 gen(std::random_device{}());
  std::uniform_int_distribution<int> dis(0, num_keys - 1);
  auto* keys = new T[num_searches];
  for (int i = 0; i < num_searches; i++) {
    int pos = dis(gen);
    keys[i] = array[pos];
  }
  return keys;
}

template <class T>
T* get_search_keys_zipf(T array[], int num_keys, int num_searches) {
  auto* keys = new T[num_searches];
  ScrambledZipfianGenerator zipf_gen(num_keys);
  for (int i = 0; i < num_searches; i++) {
    int pos = zipf_gen.nextValue();
    keys[i] = array[pos];
  }
  return keys;
}
