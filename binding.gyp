{
  "targets": [
    {
      "target_name": "nacl",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ],
      "sources": [
        "nacl.cc",
        "functions.cc",
        "tweetnacl.cpp",
        "randombytes.cpp"
      ]
    }
  ]
}
