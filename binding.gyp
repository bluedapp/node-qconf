{
  "targets": [
    {
      "target_name": "qconf",
      "sources": [ "qconf.cc" ],
      "cflags!": ["-fno-exceptions","-Wno-unused-result"],
      "cflags_cc!": ["-fno-exceptions","-Wno-unused-result"],
      "libraries": ["-lqconf"],
      "link_settings": {
        "libraries": ["-L<!(echo $QCONF_INSTALL)/lib"]
      },
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!(echo $QCONF_INSTALL)/include",
        "/usr/local/qconf/include",
        "/usr/local/include/qconf"
      ]
    }
  ]
}
