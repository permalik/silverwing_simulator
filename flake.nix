{
  description = "silverwing_simulator";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/release-24.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        name = "silverwing_simulator";
        src = ./.;
        pkgs = nixpkgs.legacyPackages.${system};
        buildInputs = with pkgs; [SDL2 SDL2.dev];
        nativeBuildInputs = with pkgs; [clang-tools];
      in {
        packages = {
          default = let
            inherit (pkgs) clangStdenv;
          in
            clangStdenv.mkDerivation {
              name = "silverwing_simulator";
              src = pkgs.lib.cleanSource ./.;
              buildInputs = with pkgs; [SDL2];

              buildPhase = with pkgs; ''
                # export CXXFLAGS="-I${SDL2.dev}/include/SDL2":
                clang++ ./src/silverwing_simulator.cpp -o silverwing_simulator -lSDL2
              '';

              installPhase = ''
                mkdir -p $out/bin
                cp silverwing_simulator $out/bin/silverwing_simulator
              '';
            };
        };
        devShells.default = pkgs.mkShell.override {stdenv = pkgs.clangStdenv;} {
          packages = with pkgs; [pkg-config clang-tools SDL2.dev alejandra];

          inputsFrom = [self.packages.${system}.default];
          # buildInputs = [
          #   pkgs.alejandra
          #   pkgs.gcc
          #   pkgs.gnumake
          #   pkgs.pkg-config
          #   pkgs.llvmPackages_19.clang-tools
          #   pkgs.SDL2
          #   # pkgs.gdb
          #   # pkgs.valgrind
          # ];

          shellHook = with pkgs; ''
            # CXXFLAGS="-I${pkgs.SDL2.dev}/include/SDL2"
            # Custom Prompt
            export PS1="\n\[\e[1;32m\][devshell](silverwing_simulator) \w\n❯ \[\e[0m\]"
          '';
        };
      }
    );
}
