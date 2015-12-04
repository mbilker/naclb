{
  "targets": [
    {
      "target_name": "nacl",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "sources": [
        "nacl.cc",
        "functions.cc",
        "tweetnacl.cpp",
        "randombytes.cpp"
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}
