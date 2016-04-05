Name:           simplehuffman
Summary:        Simple implementation of the Huffman coding
Version:        0.99999
Release:        1
License:        BSD
Group:          Archiving/Compression
URL:            http://github.com/dkukharau/simplehuffman
Packager:       Daniel Kukharau <daniel.kukharau@gmail.com>
Source:         %{name}-%{version}.tar

BuildRequires: gcc, make

%prep
%setup

%build
make

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{_bindir}
cp -f bin/huff %{buildroot}%{_bindir}/huff

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/*

%changelog
* Tue Apr 5 2016 Daniel Kukharau <daniel.kukharau@gmail.com> 0.99999-1
- Initial spec
