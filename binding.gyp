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
    }
  ]
}
