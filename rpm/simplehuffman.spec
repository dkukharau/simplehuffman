Name:           simplehuffman
Summary:        Simple implementation of the Huffman coding
Version:        %_version
Release:        %{_release_num}.%_git_commit
License:        BSD
Group:          Archiving/Compression
URL:            http://github.com/dkukharau/simplehuffman
Packager:       Daniel Kukharau <daniel.kukharau@gmail.com>
Source:         %{name}-%{version}.tar

BuildRequires: gcc, make

%description
Fast archiver based on Huffman coding algorithm

%prep
%setup

%build
make

%install
%makeinstall

%files
%defattr(-,root,root,-)
%{_bindir}/*

%changelog
